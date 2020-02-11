#include "Player.h"

#pragma region Constructors

Player::Player(GameReference ptr, int life) : m_ptr(ptr), life(life)
{
	m_ptr->textureManager.LoadAsset("player_tank", "textures/player_tank.png"); //set the appropriate textures and values
	tank_sprite.setTexture(m_ptr->textureManager.GetAsset("player_tank"));
	m_ptr->textureManager.LoadAsset("shield", "textures/shield.png");
	shield_sprite.setTexture(m_ptr->textureManager.GetAsset("shield"));
	shield_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	tank_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	tank_rectangle.setSize(sf::Vector2f(58, 58));
}

Player::~Player() {}

#pragma endregion

#pragma region Class methods

void Player::Updating(double deltaTime)
{
	sf::Time frameTime = clock_frame.restart(); 

	moving_sprite.setPosition(tank_rectangle.getPosition()); //set the sprite position according to the rectangle

	if (show_player == false)
	{
		actual_animation = &Up; //show the first frame of the animation
		show_player = true;
	}

	if (isAlive == false) //if the player is dead, block all moves
	{
		MoveUP = false;
		MoveDOWN = false;
		MoveLEFT = false;
		MoveRIGHT = false;
		SetShooted(false);
	}

	double movement = player_speed * deltaTime; //update the speed depending on the player's computer

	sf::Vector2f move(0.0f, 0.0f); //store x and y

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //go up
	{
		if (MoveUP == true)
		{
			actual_animation = &Up; //set the right sprite
			move.y -= movement; //correct the position
			direction = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //go down
	{
		if (MoveDOWN == true)
		{
			actual_animation = &Down; //set the right sprite
			move.y += movement; //correct the position
			direction = 2;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //go left
	{
		if (MoveLEFT == true)
		{
			actual_animation = &Left; //set the right sprite
			move.x -= movement; //correct the position
			direction = 3;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //go right
	{
		if (MoveRIGHT == true)
		{
			actual_animation = &Right; //set the right sprite
			move.x += movement; //correct the position
			direction = 4;
		}
	}
	else
	{
		moving_sprite.StopAnimation(); //stop the animations
	}

	moving_sprite.PlayNext(*actual_animation); //set up animations
	moving_sprite.move(move);
	moving_sprite.Updating(frameTime);
	tank_rectangle.setPosition(moving_sprite.getPosition());
	shield_sprite.setPosition(moving_sprite.getPosition());
	

	sf::Time shield_time = shield_clock.getElapsedTime();
	if (shield_time.asSeconds() > 6.0f && shield_active == true)
	{
		shield_clock.restart();
	}
	else if (shield_time.asSeconds() >= 5.0f)
	{
		shield_active = false;
	}

	movement_counter++;
	if (movement_counter >= 6) //for changes to the shield animation
		movement_counter = 0;


	if (shield_active == true) //set the sprite of the shield
	{
		if (movement_counter < 4)
			shield_sprite.setTextureRect(sf::IntRect(movement_counter * 64, 64 * 0, 64, 64));
		else
			shield_sprite.setTextureRect(sf::IntRect((movement_counter-4) * 64, 64 * 1, 64, 64));
	}
}

void Player::Input()
{
	sf::Time elapsed = projectile_clock.getElapsedTime();

	if (two_bollets == true) //the player can shoot faster
	{
		if (elapsed.asSeconds() >= fire_speed/2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				SetShooted(true); //set the shot order and reset the clock
				projectile_clock.restart();
			}
		}
	}
	if (elapsed.asSeconds() >= fire_speed) //normal shot speed
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SetShooted(true);
			projectile_clock.restart();
		}
	}
}

void Player::Drawing(double DeltaTime)
{
	m_ptr->m_window.draw(moving_sprite);

	if(shield_active==true)
	m_ptr->m_window.draw(shield_sprite);
}

void Player::Initialization()
{
	Down.SetSpriteSheet(m_ptr->textureManager.GetAsset("player_tank")); //load textures
	Left.SetSpriteSheet(m_ptr->textureManager.GetAsset("player_tank"));
	Right.SetSpriteSheet(m_ptr->textureManager.GetAsset("player_tank"));
	Up.SetSpriteSheet(m_ptr->textureManager.GetAsset("player_tank"));

	for (int i = 0; i < 6; i++)
	{
		Down.addNextFrame(sf::IntRect(i * 64, 64 * 3, 64, 64)); //arrange the frames of the animation accordingly
		Left.addNextFrame(sf::IntRect(i * 64, 64 * 2, 64, 64));
		Up.addNextFrame(sf::IntRect(i * 64, 64, 64, 64));
		Right.addNextFrame(sf::IntRect(i * 64, 0, 64, 64));
	}

	Sprite* currentAnimation = &Up; //initial position
	moving_sprite.setPosition(tank_rectangle.getPosition());
}

void Player::StopPlayer(int e_direction) //stop the player
{
	switch (e_direction)
	{
	case 1:
		MoveUP = false;
		moving_sprite.move(0, 1); //push back one pixel so that it will not get stuck in the wall
		break;
	case 2:
		MoveDOWN = false;
		moving_sprite.move(0, -1);
		break;
	case 3:
		MoveLEFT = false;
		moving_sprite.move(1, 0);
		break;
	case 4:
		MoveRIGHT = false;
		moving_sprite.move(-1, 0);
		break;
	default:
		MoveUP = false;
		MoveDOWN = false;
		MoveLEFT = false;
		MoveRIGHT = false;
		moving_sprite.move(0, 0);
		break;
	}
	tank_rectangle.setPosition(moving_sprite.getPosition()); //Update the sprite position with rectangle
}

void Player::Tier()
{
	switch (tier_level) //place variables depending on tier
	{
	case DEFAULT:
		bullet_multipler = DEFAULT;
		two_bollets = false;
		attack_demage = 10;
		break;
	case SECOND:
		bullet_multipler = SECOND;
		two_bollets = false;
		attack_demage = 10;
		break;
	case THIRD:
		bullet_multipler = SECOND;
		two_bollets = true;
		attack_demage = 10;
		break;
	case FOURTH:
		bullet_multipler = SECOND;
		two_bollets = true;
		attack_demage = 20;
		break;
	}
}

#pragma endregion

#pragma region operators

Player & Player::operator=(const Player & tmp_player) //Assignment operator (triggered when a player loses one life)
{
	if (this == &tmp_player)
	{
		return *this;
	}
	else
	{
		new(this) Player(tmp_player);
		return *this;
	}
}

Player & Player::operator++() //increment the number of player lives (object++)
{
	life++;
	return *this;
}

Player Player::operator++(int) //increment the number of player lives (++object)
{
	Player tmp_player(*this);
	++(*this);
	return tmp_player;
}

int Player::operator-(const Enemy & enemy) //Subtract the player's life depending on the damage received
{
	player_hp -= enemy.GetAD();
	if (player_hp <= 0)
	{
		life--;
		player_hp = 100;

		if (life <= 0)
		{
			isAlive = false;
		}
		return 0;
	}
	return player_hp;
}

void Player::operator() (int a, int b) //set tier
{
	if (tier_level < FOURTH && tier_level >= DEFAULT)
	{
		tier_level += a;
	}
	else if (tier_level <= 0)
	{
		tier_level = b;
	}
	std::cout << tier_level << std::endl;
}

Player & Player::operator--() //decrement player's life
{
	life--;
	return *this;
}

#pragma endregion

#pragma region Accessors

void Player::SetPlayerCollision(bool player_collision)
{
	this->player_collision = player_collision; //set the collision status of the player
}

void Player::SetRectangle(sf::RectangleShape player_rectangle)
{
	this->tank_rectangle = player_rectangle; //set rectangle
}

void Player::SetShieldStatus(bool shield_active)
{
	this->shield_active = shield_active; //set status shield
}

bool Player::GetPlayerCollision() const
{
	return this->player_collision; //return status collision
}

int Player::GetPlayerHP() const
{
	return this->player_hp; //return player;s hp
}

bool Player::GetShieldStatus() const
{
	return this->shield_active; //return shield status
}

int Player::GetMultipler() const
{
	return this->bullet_multipler; //return bullet multipler
}

int Player::GetLife() const
{
	return this->life; //return the number of lives 
}

#pragma endregion