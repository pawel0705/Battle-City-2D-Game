#include "Enemy.h"

#pragma region Constructors

Enemy::Enemy()
{}

Enemy::Enemy(sf::RectangleShape base_rectangle, GameReference ptr) : base_rectangle(base_rectangle), m_ptr(ptr)
{
	m_ptr->textureManager.LoadAsset("enemy_tank", "textures/enemy_tank.png"); //load textures
	tank_sprite.setTexture(m_ptr->textureManager.GetAsset("enemy_tank"));
	m_ptr->textureManager.LoadAsset("hammer_time", "textures/hammer_time.png");
	spawning_sprite.setTexture(m_ptr->textureManager.GetAsset("hammer_time"));
	m_ptr->textureManager.LoadAsset("timer", "textures/timer.png");
	timer_sprite.setTexture(m_ptr->textureManager.GetAsset("timer"));
	spawning_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	timer_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	tank_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	tank_rectangle.setSize(sf::Vector2f(60, 60));
	enemy_view.setSize(sf::Vector2f(64 * 7, 64 * 7));
	enemy_view.setPosition(0, 0);
	enemy_view.setFillColor(sf::Color::Green);
}

Enemy::~Enemy() {}

#pragma endregion

#pragma region Operators

Enemy & Enemy::operator=(const Enemy & enemy) noexcept //assignment operator
{
	if (this == &enemy)
	{
		return *this;
	}
	else
	{
		new(this) Enemy(enemy);
		return *this;
	}
}

#pragma endregion

#pragma region  Class methods

void Enemy::StopTime()
{
	freeze = true; //freeze enemy
}

void Enemy::Algorithm(sf::RectangleShape player_rectangle)
{
	if (freeze == true) //if it is stopped, exit the function
		return;

	int choice = static_cast<int>(rand() % 20); //make a choice
	
	//attack player
	if (enemy_view.getGlobalBounds().intersects(player_rectangle.getGlobalBounds())) //follow player
	{
		chasing_player = true;
		if (choice == 0)
		{
			if (tank_rectangle.getPosition().y < player_rectangle.getPosition().y)
			{
				direction = 2;
			}
			else if (tank_rectangle.getPosition().y > player_rectangle.getPosition().y)
			{
				direction = 1;
			}
		}
		if (choice == 1)
		{
			if (tank_rectangle.getPosition().x < player_rectangle.getPosition().x)
			{
				direction = 4;
			}
			else if (tank_rectangle.getPosition().x > player_rectangle.getPosition().x)
			{
				direction = 3;
			}
		}
		what_to_do = true;
	}
	else
	{
		what_to_do = false;
		chasing_player = false;
	}

	//attack base
	if (chasing_player == false)
	{
		
	if (enemy_view.getGlobalBounds().intersects(base_rectangle.getGlobalBounds())) //go to base
	{
		destroying_base = true;
		if (choice == 0)
		{
			if (tank_rectangle.getPosition().y < base_rectangle.getPosition().y)
			{
				direction = 2;
			}
			else if (tank_rectangle.getPosition().y > base_rectangle.getPosition().y)
			{
				direction = 1;
			}
		}
		if (choice == 1)
		{
			if (tank_rectangle.getPosition().x < base_rectangle.getPosition().x)
			{
				direction = 4;
			}
			else if (tank_rectangle.getPosition().x > base_rectangle.getPosition().x)
			{
				direction = 3;
			}
		}
		what_to_do = true;
	}
	else
	{
		what_to_do = false;
		destroying_base = false;
	}
	}
}

void Enemy::Updating(double deltaTime) 
{
	sf::Time frameTime = clock_frame.restart(); //count down the time between frames
	sf::Time stop_time = stop_time_clock.getElapsedTime(); //the opponent can not do anything
	 
	if (stop_time.asSeconds() > 15.0f)
	{
		stop_time_clock.restart();
	}

	if (freeze == true)
	{
		movement_counter++;
		if (movement_counter >= 16)
			movement_counter = 0;
		timer_sprite.setTextureRect(sf::IntRect(movement_counter/4 * 64, 64 * 0, 64, 64)); //if he was stopped, show the right animation
		timer_sprite.setPosition(tank_rectangle.getPosition());

		if (stop_time.asSeconds() > 10.0f)
		{
			freeze = false;
			stop_time_clock.restart();
		}
		return;
	}

	movement_counter++;
	if (movement_counter >= 6)
		movement_counter = 0;
	
	enemy_direction_length++;
	if (enemy_direction_length >= 20) //how far can the opponent go without making a decision to change direction
	{
		if(what_to_do==false)
		direction = Randomize();
		enemy_direction_length = 0;
	}

	double movement = enemy_speed * deltaTime; //set the speed depending on the "delta Time" so that the opponent moves at the same speed on different computers

	if (hammer_elapsed < 3) //animation of the appearance of the opponent
	{
		hammer_length++;
		if (hammer_length >= 20)
		{
			hammer_length = 0;
			hammer_elapsed++;
		}
		spawning_sprite.setTextureRect(sf::IntRect(hammer_length / 4 * 64, 64 * 0, 64, 64));
	}

	if (hammer_elapsed < 3)
		return;

	if (show_enemy == false)
	{
		actual_animation = &Up;
		show_enemy = false;
	}

	sf::Vector2f move(0.0f, 0.0f);

	switch (direction) //move enemy
	{
	case 1:
		if (MoveUP == true)
		{
			actual_animation = &Up;
			move.y -= movement;
			ResetMovement();
		}
		break;
	case 2:
		if (MoveDOWN == true)
		{
			actual_animation = &Down;
			move.y += movement;
			ResetMovement();
		}
		break;
	case 3:
		if (MoveLEFT == true)
		{
			actual_animation = &Left;
			move.x -= movement;
			ResetMovement();
		}
		break;
	case 4:
		if (MoveRIGHT == true)
		{
			actual_animation = &Right;
			move.x += movement;
			ResetMovement();
		}
		break;
	default:
		moving_sprite.StopAnimation();
		ResetMovement();
		break;
	}

	moving_sprite.PlayNext(*actual_animation); //update animation
	moving_sprite.move(move);
	moving_sprite.Updating(frameTime);
	tank_rectangle.setPosition(moving_sprite.getPosition());
	enemy_view.setPosition(tank_rectangle.getPosition().x - 192, tank_rectangle.getPosition().y - 192);
}

int Enemy::Randomize() //randomize
{
	std::default_random_engine engine;
	std::uniform_real_distribution<double> distribution(0, 10);

	auto time = std::chrono::system_clock::now();
	auto interwal = time.time_since_epoch();
	engine.seed(interwal.count());

	return distribution(engine); //return random value
}

void Enemy::Initialization()
{
	spawning_sprite.setPosition(tank_rectangle.getPosition());

	Down.SetSpriteSheet(m_ptr->textureManager.GetAsset("enemy_tank")); //set textures
	Left.SetSpriteSheet(m_ptr->textureManager.GetAsset("enemy_tank"));
	Right.SetSpriteSheet(m_ptr->textureManager.GetAsset("enemy_tank"));
	Up.SetSpriteSheet(m_ptr->textureManager.GetAsset("enemy_tank"));

	for (int i = 0; i < 6; i++)
	{
		Down.addNextFrame(sf::IntRect(i * 64, 64 * 3, 64, 64)); //set frames
		Left.addNextFrame(sf::IntRect(i * 64, 64 * 2, 64, 64));
		Up.addNextFrame(sf::IntRect(i * 64, 64, 64, 64));
		Right.addNextFrame(sf::IntRect(i * 64, 0, 64, 64));
	}

	Sprite* currentAnimation = &Up; //set first frame
	moving_sprite.setPosition(tank_rectangle.getPosition());
}

void Enemy::Input()
{
	if (freeze == true) //if enemy is freezed, return
		return;

	if (hammer_elapsed < 3) //if the spawning animation is not over yet, return
		return;

	sf::Time elapsed = shooting_clock.getElapsedTime();
	
		if (Randomize() == 1) //randomize direction
		{
			if (direction <= 4 && direction >= 1)
			{
				if (elapsed.asSeconds() >= 1.0f)
				{
					shoot = true;
					shooting_clock.restart();
				}
			}
		}
		else
		{
			shoot = false;
		}
}

void Enemy::Drawing(double deltaTime)
{
	m_ptr->m_window.draw(moving_sprite);

	if (hammer_elapsed < 3) //draw spawning sprite
	{
		m_ptr->m_window.draw(spawning_sprite);
	}

	if (freeze == true) //if enemy freezed, draw timer
	{
		m_ptr->m_window.draw(timer_sprite);
	}
}

void Enemy::StopEnemy(int e_direction) //stop enemy
{
	switch (e_direction)
	{
	case 1:
		MoveUP = false;
		moving_sprite.move(0, 1); //move away from the wall by 1 pixel so that it does not get stuck in it
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
	tank_rectangle.setPosition(moving_sprite.getPosition()); //Update the location of the sprite with rectangle
}

#pragma endregion