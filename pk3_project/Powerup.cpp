#include "Powerup.h"

#pragma region Constructors

Powerup::Powerup(GameReference m_ptr) : m_ptr(m_ptr)
{
	m_ptr->textureManager.LoadAsset("powerups", "textures/powerups.png");
	powerup_sprite.setTexture(m_ptr->textureManager.GetAsset("powerups"));
	powerup_rectangle.setSize(sf::Vector2f(64, 64));
}

#pragma endregion

#pragma region Class methods

void Powerup::Input()
{
	//nothing here
}

void Powerup::Drawing(double deltatime)
{
	if (couneter_life > 400)
	{
		if(couneter_life % 20 >= 0 && couneter_life % 20 <= 5) //if the life expectancy exceeds a certain value, draw "flashing" power up
			m_ptr->m_window.draw(powerup_sprite);
	}
	else
		m_ptr->m_window.draw(powerup_sprite); //draw powerup
}

void Powerup::Updating(double deltatime)
{
	couneter_life++;
	if (couneter_life > life_time) //heck the lifetime of the bonus, if it is exceeded, send the appropriate information
	{
		delete_powerup = true;
		couneter_life = 0;
	}

	powerup_sprite.setPosition(powerup_rectangle.getPosition());
}

void Powerup::Initialization()
{
	random = Randomize(GRENADE, TIMER + 1); //draw the type of bonus
	switch (random) //depending on the type of bonus selected, set the appropriate part of the texture
	{
	case GRENADE:
		powerup_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		break;
	case HELMET:
		powerup_sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
		break;
	case TANK:
		powerup_sprite.setTextureRect(sf::IntRect(64 * 2, 0, 64, 64));
		break;
	case SHOVEL:
		powerup_sprite.setTextureRect(sf::IntRect(0, 64, 64, 64));
		break;
	case STAR:
		powerup_sprite.setTextureRect(sf::IntRect(64 * 1, 64, 64, 64));
		break;
	case TIMER:
		powerup_sprite.setTextureRect(sf::IntRect(64 * 2, 64, 64, 64));
		break;
	default:
		//powerup_sprite.setTextureRect(sf::IntRect(64 * 2, 0, 64, 64));
		break;
	}
	bonus_type = random;
}

int Powerup::Randomize(float from, float to) //drawing a number from the range
{
		std::default_random_engine engine;
		std::uniform_real_distribution<double> distribution(from, to);

		auto time = std::chrono::system_clock::now();
		auto interwal = time.time_since_epoch();
		engine.seed(interwal.count());

		return distribution(engine); //return the drawn number
}

void Powerup::Grenade(std::vector<Enemy*> &enemy_array, std::vector<Enemy*>::const_iterator &Iter_enemy, int *nr_of_enemies_now, int *destroyed_enemies, std::vector<Explosion*>& explosion_array, Explosion *m_explosion) //the function responsible for the "grenade" bonus
{
	for (int i = 0; i < *nr_of_enemies_now; i++) //go in the loop of all opponents who are currently on the map
	{
		for (Iter_enemy = enemy_array.begin(), iterator_1 = 0; Iter_enemy != enemy_array.end(); Iter_enemy++, iterator_1++)
		{
			m_explosion = new Explosion(enemy_array[iterator_1]->GetRectangle().getPosition(), m_ptr, true); //set up explosions
			m_explosion->Initialization();
			explosion_array.push_back(m_explosion);
			delete enemy_array[iterator_1]; //remove the opponent
			enemy_array.erase(Iter_enemy);
			*destroyed_enemies++;
			break;
		}
	}

	*nr_of_enemies_now = 0; //Reset the number of enemies on the map
	delete_powerup = true; //set information about the removal of the powerup
}

void Powerup::Helmet(Player *player, std::vector<Projectile*> &projectile_array, std::vector<Projectile*>::const_iterator &iter_proj) //"helmet" bonus
{
	player->SetShieldStatus(true); //set the shield status on 'true'
	int iterator_1 = 0;

	for (iter_proj = projectile_array.begin(); iter_proj != projectile_array.end(); iter_proj++, iterator_1++) //change the status of all currently launched missiles to "neutral" so that the player is not wounded
	{
		if (projectile_array[iterator_1]->GetProjectileStatus() == 2)
		{
			projectile_array[iterator_1]->SetProjectileStatus(0);
		}
	}

	delete_powerup = true; //remove powerup
}

void Powerup::Shovel(std::vector<MapCube>::const_iterator &Iter_wall, std::vector<MapCube> &wall_array, std::vector<MapCube> &base_walls) //function responsible for power up "shovel"
{
	int iterator_1 = 0;
	for (Iter_wall = wall_array.begin(); Iter_wall != wall_array.end(); Iter_wall++, iterator_1++) //search for walls marked as "walls belonging to the base"
	{
		if (wall_array[iterator_1].GetIsBaseWalls() == true) //remove old walls
		{
			wall_array[iterator_1].SetisDestroyed(true);
		}
	}
	for (Iter_wall = base_walls.begin(), iterator_1 = 0; Iter_wall != base_walls.end(); Iter_wall++, iterator_1++) //set new walls
	{
		sf::RectangleShape tmp_rectangle;
		tmp_rectangle = base_walls[iterator_1].GetRectangle();
		MapCube harder_rock(m_ptr, 40, true, true);
		harder_rock.SetRectanglePosition(tmp_rectangle.getPosition().x, tmp_rectangle.getPosition().y);
		harder_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64, 0, 64, 64));
		wall_array.push_back(harder_rock);
	}
	delete_powerup = true; //remove powerup
}

void Powerup::Timer(std::vector<Enemy*> &enemy_array, std::vector<Enemy*>::const_iterator &Iter_enemy) //function responsible for the "timer" bonus
{
	int iterator_1 = 0;
	for (Iter_enemy = enemy_array.begin(); Iter_enemy != enemy_array.end(); Iter_enemy++, iterator_1++) //call on all enemies the function responsible for their maintenance
	{
		enemy_array[iterator_1]->StopTime();
	}
	delete_powerup = true; //remove powerup
}

void Powerup::Tank(Player *player) //the function responsible for handling the "tank" bonus
{
	player++; //increment the player's life
	delete_powerup = true;
}

void Powerup::Star(Player *player) //the function responsible for handling the "star" bonus
{
	player->operator()(1, 1); //set the appropriate player tier
	player->Tier();
	delete_powerup = true; //remove powerup
}

void Powerup::RandomisePosition(int x, int y) //draw the position of the bonus on the map
{
	powerup_rectangle.setPosition(Randomize(0, 64 * x), Randomize(0, 64 * y));
}

#pragma endregion

#pragma region Accessors

sf::RectangleShape Powerup::GetRectangle() const
{
	return this->powerup_rectangle; //return powerup's rectangle
}

void Powerup::SetRectanglePosition(const sf::Vector2f & position)
{
	this->powerup_rectangle.setPosition(position); //set rectangle position
}

int Powerup::GetPowerup() const
{
	return this->bonus_type; //return type of bonus
}

bool Powerup::GetIsDeleted() const
{
	return this->delete_powerup; //return information about the removal of the bonus from the map
}

#pragma endregion