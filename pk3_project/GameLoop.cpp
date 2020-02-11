#include "GameLoop.h"

#pragma region Constructors

GameLoop::GameLoop(std::string string_tmp, GameReference ptr)
	: m_ptr(ptr), string_tmp(string_tmp),
	hud("SCORE: 0", 45, sf::Vector2f(0, 0), m_ptr->fontManager.GetAsset("Modia")), //set the appropriate values
	nr_enemies("ENEMIES\nKILLED: 0", 45, sf::Vector2f(0, 0), m_ptr->fontManager.GetAsset("Modia")),
	hp_status("HP: 100/100\nLIFE: 2", 45, sf::Vector2f(0, 0), m_ptr->fontManager.GetAsset("Modia"))
{
	m_player = new Player(m_ptr, 3); //create player
	m_player->Initialization(); //initialize player
	view.setSize(sf::Vector2f(m_ptr->m_window.getSize().x, m_ptr->m_window.getSize().y)); //set camera on middle window
	view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
	m_ptr->m_window.setView(view);
}

GameLoop::~GameLoop()
{
	delete m_player; //delete player

	while (!proj_array.empty()) //delete projectiles
	{
		delete proj_array.back();
		proj_array.pop_back();
	}

	while (!enemy_array.empty()) //detete enemies
	{
		delete enemy_array.back();
		enemy_array.pop_back();
	}

	while (!powerup_array.empty()) //delete powerups
	{
		delete powerup_array.back();
		powerup_array.pop_back();
	}

	while (!text_array.empty()) //delete text arrays
	{
		delete text_array.back();
		text_array.pop_back();
	}

	while (!explosion_array.empty()) //delete explosions
	{
		delete explosion_array.back();
		explosion_array.pop_back();
	}
}

#pragma endregion

#pragma region  Class methods

void GameLoop::Initialization()
{
	m_ptr->textureManager.LoadAsset("game_border", "textures/game_border.png"); //load texture hud from file
	Sprite_Ground.setTexture(m_ptr->textureManager.GetAsset("game_border"));
	MapFile map(string_tmp);
	map.LoadMap();
	sizeX = map.sizeX;
	sizeY = map.sizeY;
	for (int i = 0; i < map.sizeX; i++) //read map from file
	{
		for (int j = 0; j < map.sizeY; j++)
		{
			if (map.map[i][j] == 1) //normal rock
			{
				MapCube normal_rock(m_ptr, 20, true);
				normal_rock.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				normal_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 0, 64, 64));
				wall_array.push_back(normal_rock);
			}
			else if (map.map[i][j] == 2) //harder rock
			{
				MapCube harder_rock(m_ptr, 40, true);
				harder_rock.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				harder_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64, 0, 64, 64));
				wall_array.push_back(harder_rock);
			}
			else if (map.map[i][j] == 3) //water
			{
				MapCube water(m_ptr, true);
				water.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				water.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64, 64, 64, 64));
				wall_array.push_back(water);
			}
			else if (map.map[i][j] == 4) //bush
			{
				MapCube bush(m_ptr, true, true);
				bush.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				bush.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 2, 0, 64, 64));
				wall_array.push_back(bush);
			}
			else if (map.map[i][j] == 5) //indestructible rock
			{
				MapCube bad_rock(m_ptr);
				bad_rock.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				bad_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 64, 64, 64));
				wall_array.push_back(bad_rock);
			}
			else if (map.map[i][j] == 6) //player's base
			{
				MapCube your_base(m_ptr, 200, true, true, true);
				your_base.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				tmp_rectangle = your_base.GetRectangle();
				your_base.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 2, 64, 64, 64));
				wall_array.push_back(your_base);
			}
			else if (map.map[i][j] == 7) //player's spawn point
			{
				MapCube spawn_point(m_ptr, true, true);
				spawn_point.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				m_player->SetRectanglePosition(spawn_point.GetRectangle().getPosition());
				spawn_point_rectangle = spawn_point.GetRectangle();
			}
			else if (map.map[i][j] == 8) //enemy's spawn point
			{
				MapCube enemy_spawn_point(m_ptr, true, true, true);
				std::cout << "push" << std::endl;
				enemy_spawn_point.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				wall_array.push_back(enemy_spawn_point);
			}
			else if (map.map[i][j] == 9) //base rock
			{
				MapCube base_rock(m_ptr, 20, true, true);
				base_rock.SetRectanglePosition(i * 64 + 64, j * 64 + 64);
				base_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 0, 64, 64));
				wall_array.push_back(base_rock);
				base_walls.push_back(base_rock);
			}
		}
	}

	iterator_1 = 0;
	for (const auto & iter_wall : wall_array)
	{
		if (wall_array[iterator_1].GetisEnemySpawnPoint() == true) //create as many opponents as there are spawns on the map
		{
			m_enemy = new Enemy(tmp_rectangle, m_ptr);
			m_enemy->SetRectanglePosition(wall_array[iterator_1].GetRectangle().getPosition());
			enemy_array.push_back(m_enemy);
			m_enemy->Initialization();
			spawned_enemies++;
			nr_of_enemies_now++;
		}
		iterator_1++;
	}
	hp_status.GetPlayerMaxHP(m_player->GetPlayerHP(), m_player->GetLife());
}

void GameLoop::Input()
{
	sf::Event event;

	while (m_ptr->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) //check if the user has clicked the red cross
		{
			m_ptr->m_window.close();
		}
		m_player->Input();
	}
}

void GameLoop::CameraUpdate() //update the position of the camera depending on the player's movement
{
	view.setCenter(m_player->GetRectangle().getPosition().x + 200, m_player->GetRectangle().getPosition().y);
	hud.setPosition(m_player->GetRectangle().getPosition().x + 16 + m_ptr->m_window.getSize().x / 2 - 128, m_player->GetRectangle().getPosition().y - m_ptr->m_window.getSize().y / 2 + 256);
	nr_enemies.setPosition(m_player->GetRectangle().getPosition().x + 16 + m_ptr->m_window.getSize().x / 2 - 128, m_player->GetRectangle().getPosition().y - m_ptr->m_window.getSize().y / 2 + 128);
	hp_status.setPosition(m_player->GetRectangle().getPosition().x + 16 + m_ptr->m_window.getSize().x / 2 - 128, m_player->GetRectangle().getPosition().y - m_ptr->m_window.getSize().y / 2 + 384);
	Sprite_Ground.setPosition(m_player->GetRectangle().getPosition().x + 200 - m_ptr->m_window.getSize().x / 2, m_player->GetRectangle().getPosition().y - m_ptr->m_window.getSize().y / 2);
	m_ptr->m_window.setView(view);
}

void GameLoop::Updating(double deltaTime)
{
	//-----UPDATING PLAYER-----//
	m_player->Updating(deltaTime);

	if (m_player->GetShooted()) //a new projectile if the player shooted
	{
		m_bullet = new Projectile(m_ptr);
		m_bullet->SetRectanglePosition(m_player->GetRectangle().getPosition().x + m_player->GetRectangle().getSize().x / 4, m_player->GetRectangle().getPosition().y + m_player->GetRectangle().getSize().y / 4);
		m_bullet->SetDirection(m_player->GetDirection());
		m_bullet->SetProjectileStatus(1);
		m_bullet->operator*=(m_player->GetMultipler());
		proj_array.push_back(m_bullet);
		m_player->SetShooted(false);
	}

	//---UPDATING ENEMY-----//
	iterator_1 = 0;
	for (const auto & iter_enemy : enemy_array)
	{
		enemy_array[iterator_1]->Algorithm(m_player->GetRectangle()); //call the functions responsible for changes in the opponent's state
		enemy_array[iterator_1]->Updating(deltaTime);
		enemy_array[iterator_1]->Input();

		if (enemy_array[iterator_1]->GetShooted() == true) ////a new projectile if the enemy shooted
		{
			m_bullet = new Projectile(m_ptr);
			m_bullet->SetRectanglePosition(enemy_array[iterator_1]->GetRectangle().getPosition().x + enemy_array[iterator_1]->GetRectangle().getSize().x / 4, enemy_array[iterator_1]->GetRectangle().getPosition().y + enemy_array[iterator_1]->GetRectangle().getSize().y / 4);
			m_bullet->SetDirection(enemy_array[iterator_1]->GetDirection());

			if (m_player->GetShieldStatus() == true)
				m_bullet->SetProjectileStatus(0);
			else
				m_bullet->SetProjectileStatus(2);

			proj_array.push_back(m_bullet);
		}
		iterator_1++;
	}

	//create a new opponent if it is less than the enemy spawn on the map
	if ((nr_of_enemies_now < spawned_enemies) && (max_enemies - spawned_enemies > destroyed_enemies - 1))
	{
		iterator_1 = 0;
		for (const auto & iter_wall : wall_array)
		{
			while (nr_of_enemies_now < spawned_enemies)
			{
				if (wall_array[iterator_1].GetisEnemySpawnPoint() == true)
				{
						m_enemy = new Enemy(tmp_rectangle, m_ptr);
						m_enemy->SetRectanglePosition(wall_array[iterator_1].GetRectangle().getPosition());
						enemy_array.push_back(m_enemy);
						m_enemy->Initialization();
						nr_of_enemies_now++;
				}
				iterator_1++;
			}
		}
	}

	//----UPDATING PROJECTILE----//
	iterator_1 = 0;
	for (const auto & iter_proj : proj_array)
	{
		proj_array[iterator_1]->Updating(deltaTime);
		iterator_1++;
	}

	//----UPDATING POWERUP---//
	iterator_1 = 0;
	for (const auto & iter_powerup : powerup_array)
	{
		powerup_array[iterator_1]->Updating(deltaTime);
		iterator_1++;
	}

	//---UPDATING TEXT---//
	iterator_1 = 0;
	for (const auto & iter_text : text_array)
	{
		text_array[iterator_1]->Updating(deltaTime);
		iterator_1++;
	}

	//----ADDITIONAL FUNCTIONS---//
	if (game_over == false)
	{
		CameraUpdate();
	}
	Collision();
	SpawnPowerUp();
	Deleting();
	isOver();
}

void GameLoop::Drawing(double deltaTime)
{
	if (draw_hud == true)
	{
		m_ptr->m_window.draw(Sprite_Ground); //draw background
	}
	m_player->Drawing(deltaTime); //draw player

	//----DRAW ENEMY----//
	iterator_1 = 0;
	for (const auto & iter_enemy : enemy_array)
	{
		enemy_array[iterator_1]->Drawing(deltaTime);
		iterator_1++;
	}

	//--------DRAW WALL-----------//
	iterator_1 = 0;
	for (const auto & iter_wall : wall_array)
	{
		wall_array[iterator_1].Drawing(deltaTime);
		m_ptr->m_window.draw(wall_array[iterator_1].GetSprite());
		iterator_1++;
	}

	//----DRAW POWERUP---//
	iterator_1 = 0;
	for (const auto & iter_powerup : powerup_array)
	{
		powerup_array[iterator_1]->Drawing(deltaTime);
		iterator_1++;
	}

	//------DRAW PROJECTILE---------//
	iterator_1 = 0;
	for (const auto & iter_proj : proj_array)
	{
		proj_array[iterator_1]->Drawing(deltaTime);
		iterator_1++;
	}

	//------DRAW EXPLOSIONS-----//
	iterator_1 = 0;
	for (const auto & iter_explosion : explosion_array)
	{
		explosion_array[iterator_1]->Updating(deltaTime);
		explosion_array[iterator_1]->Drawing(deltaTime);
		iterator_1++;
	}

	//----DRAW HUD---//
	m_ptr->m_window.draw(Sprite_Ground);
	m_ptr->m_window.draw(nr_enemies);
	m_ptr->m_window.draw(hud);
	m_ptr->m_window.draw(hp_status);

	iterator_1 = 0;
	for (const auto & iter_text : text_array) //draw text information
	{
		text_array[iterator_1]->SetTextPosition(view.getCenter());
		text_array[iterator_1]->Drawing(deltaTime);
		iterator_1++;
	}
}

void GameLoop::Collision()
{
	//-----COLLISION PLAYER AND ENEMY WITH WALLS-------//
	iterator_1 = 0;
	for (const auto & iter_wall : wall_array)
	{
		if (wall_array[iterator_1].GetisCollidable() == false)
		{
			while (m_player->GetRectangle().getGlobalBounds().intersects(wall_array[iterator_1].GetRectangle().getGlobalBounds()))
			{
				m_player->StopPlayer(m_player->GetDirection());
			}
			m_player->ResetMovement();
			iterator_2 = 0;

			for (const auto & iter_enemy : enemy_array)
			{
				while (enemy_array[iterator_2]->GetRectangle().getGlobalBounds().intersects(wall_array[iterator_1].GetRectangle().getGlobalBounds()))
				{
					enemy_array[iterator_2]->StopEnemy(enemy_array[iterator_2]->GetDirection());
				}
				enemy_array[iterator_2]->ResetMovement();
				iterator_2++;
			}
		}
		iterator_1++;
	}

	//------PROJECTILE COLLISION WITH ENEMY AND PLAYER------//
	iterator_1 = 0;
	for (const auto & iter_proj : proj_array)
	{
		iterator_2 = 0;
		for (const auto & iter_enemy : enemy_array)
		{
			if (proj_array[iterator_1]->GetRectangle().getGlobalBounds().intersects(enemy_array[iterator_2]->GetRectangle().getGlobalBounds()))
			{
				if (proj_array[iterator_1]->GetProjectileStatus() == 1)
				{
					proj_array[iterator_1]->SetDestroyed(true);
					enemy_array[iterator_2]->SetIsAlive(false);
					hud + 100;
				}
			}
			if (proj_array[iterator_1]->GetRectangle().getGlobalBounds().intersects(m_player->GetRectangle().getGlobalBounds()))
			{
				if (proj_array[iterator_1]->GetProjectileStatus() == 2)
				{
					proj_array[iterator_1]->SetDestroyed(true);
					hp_status - *enemy_array[iterator_2];
					int tmp = *m_player - *enemy_array[iterator_2];
					if (tmp <= 0)
					{
						if (m_player->GetLife() <= 0)
						{
							m_player->SetIsAlive(false);
							break;
						}
						*m_player = Player(m_ptr, m_player->GetLife());
						m_player->Initialization();
						m_player->SetRectanglePosition(spawn_point_rectangle.getPosition());
						++hp_status;
					}
				}
				break;
			}
			iterator_2++;
		}
		iterator_1++;
	}

	//----PROJECTILE COLLIDING WITH WALL------//
	iterator_1 = 0;
	for (const auto & iter_proj : proj_array)
	{
		iterator_2 = 0;
		for (const auto & iter_wall : wall_array)
		{
			if (proj_array[iterator_1]->GetRectangle().getGlobalBounds().intersects(wall_array[iterator_2].GetRectangle().getGlobalBounds()))
			{
				if (wall_array[iterator_2].GetCanShotThrough() == false)
				{
					proj_array[iterator_1]->SetDestroyed(true);
					if (wall_array[iterator_2].GetCanDestroy() == true)
					{
						if (proj_array[iterator_1]->GetProjectileStatus() == 1)
						{
							hud++;
						}
						tmp_i = wall_array[iterator_2].GetHP();
						tmp_i -= m_player->GetAD();
						wall_array[iterator_2].SetHP(tmp_i);

						if (wall_array[iterator_2].GetHP() <= 0)
						{
							m_explosion = new Explosion(wall_array[iterator_2].GetRectangle().getPosition(), m_ptr);
							m_explosion->Initialization();
							explosion_array.push_back(m_explosion);
							wall_array[iterator_2].SetisDestroyed(true);
							nr_base_array = iterator_2;
							if (wall_array[iterator_2].GetIsBase() == true)
							{
								end_game = true;
							}
						}
					}
				}
			}
			iterator_2++;
		}
		iterator_1++;
	}
}

void GameLoop::Deleting()
{
	//----DELETE WALL----//
	for (Iter_wall = wall_array.begin(), iterator_1 = 0; Iter_wall != wall_array.end(); Iter_wall++, iterator_1++)
	{
		if (wall_array[iterator_1].GetisDestroyed() == true)
		{
			wall_array.erase(Iter_wall);
			break;
		}
	}

	//--------DELETE PROJECTILE----------//
	for (Iter = proj_array.begin(), iterator_1 = 0; Iter != proj_array.end(); Iter++, iterator_1++)
	{
		if (proj_array[iterator_1]->GetDestroyed() == true)
		{
			m_explosion = new Explosion(proj_array[iterator_1]->GetRectangle().getPosition(), m_ptr);
			m_explosion->Initialization();
			explosion_array.push_back(m_explosion);
			delete proj_array[iterator_1];
			proj_array.erase(Iter);
			//delete *Iter;
			break;
		}
	}

	//------DELETE ENEMY-------//
	for (Iter_enemy = enemy_array.begin(), iterator_1 = 0; Iter_enemy != enemy_array.end(); Iter_enemy++, iterator_1++)
	{
		if (enemy_array[iterator_1]->GetIsAlive() == false)
		{
			nr_enemies++;
			destroyed_enemies++;
			nr_of_enemies_now--;
			m_explosion = new Explosion(enemy_array[iterator_1]->GetRectangle().getPosition(), m_ptr, true);
			m_explosion->Initialization();
			explosion_array.push_back(m_explosion);
			delete enemy_array[iterator_1];
			enemy_array.erase(Iter_enemy);
			break;
		}
	}

	//----DELETE EXPLOSION----//
	for (Iter_explosion = explosion_array.begin(), iterator_1 = 0; Iter_explosion != explosion_array.end(); Iter_explosion++, iterator_1++)
	{
		if (explosion_array[iterator_1]->GetIsDeleted() == true)
		{
			delete explosion_array[iterator_1];
			explosion_array.erase(Iter_explosion);
			break;
		}
	}

	//---DELETE POWERUP----//
	for (iter_powerup = powerup_array.begin(), iterator_1 = 0; iter_powerup != powerup_array.end(); iter_powerup++, iterator_1++)
	{
		if (powerup_array[iterator_1]->GetIsDeleted())
		{
			delete powerup_array[iterator_1];
			powerup_array.erase(iter_powerup);
			break;
		}
	}

	//----DELETE TEXT----//
	for (iter_text = text_array.begin(), iterator_1 = 0; iter_text != text_array.end(); iterator_1++, iter_text++)
	{
		if (text_array[iterator_1]->GetDeleteText())
		{
			delete text_array[iterator_1];
			text_array.erase(iter_text);
			break;
		}
	}
}

void GameLoop::isOver() //a function that checks for the condition of the end of the game
{
	if (max_enemies == nr_enemies.nr_enemies_killed || end_game == true || m_player->GetIsAlive() == false)
	{
		game_over = true;
		draw_hud = false;
		sf::Time elapsed1 = wait_to_score_state.getElapsedTime();
		if (m_player->GetIsAlive() == false) //the player died
		{
			if (tmp_bool == false)
			{
				text = new ShowText(m_ptr, 1);
				text->Initialization();
				text->SetTextPosition(view.getCenter());
				text_array.push_back(text);
				m_explosion = new Explosion(m_player->GetRectangle().getPosition(), m_ptr, true);
				m_explosion->Initialization();
				explosion_array.push_back(m_explosion);
				tmp_bool = true;
				wait_to_score_state.restart();
			}
		}
		if (end_game == true) //the base was destroyed
		{
			if (tmp_bool == false)
			{
				text = new ShowText(m_ptr, 2);
				text->Initialization();
				text->SetTextPosition(view.getCenter());
				text_array.push_back(text);
				tmp_bool = true;
				wait_to_score_state.restart();
			}
		}
		if (max_enemies == nr_enemies.nr_enemies_killed) //all opponents have been destroyed
		{
			if (tmp_bool == false)
			{
				text = new ShowText(m_ptr, 3);
				text->Initialization();
				text->SetTextPosition(view.getCenter());
				text_array.push_back(text);
				tmp_bool = true;
				wait_to_score_state.restart();
			}
		}

		elapsed1 = wait_to_score_state.getElapsedTime();
		if (elapsed1.asSeconds() >= 5.0f)
		{
			view.setCenter(m_ptr->m_window.getSize().x / 2, m_ptr->m_window.getSize().y / 2);
			m_ptr->m_window.setView(view);
			//after 5 seconds, go to the "game over" state
			m_ptr->m_stateMachine.AddNewState(StateReference(new GameOver(hud, nr_enemies, this->m_ptr)));
			this->~GameLoop();
		}
	}
}

void  GameLoop::SpawnPowerUp()
{
	sf::Time elapsed = generate_powerup.getElapsedTime();
	if (elapsed.asSeconds() >= 10.0f) //Create a bonus every 10 seconds
	{
		m_powerup = new Powerup(m_ptr);
		m_powerup->Initialization();
		m_powerup->RandomisePosition(sizeX, sizeY);
		powerup_array.push_back(m_powerup);
		generate_powerup.restart();
	}

	//----PLAYER PICKING POWER UP----//
	iterator_1 = 0;
	for (const auto & iter_powerup : powerup_array)
	{
		if (m_player->GetRectangle().getGlobalBounds().intersects(powerup_array[iterator_1]->GetRectangle().getGlobalBounds()))
		{
			switch (powerup_array[iterator_1]->GetPowerup())
			{
			case 0:
				powerup_array[iterator_1]->Grenade(enemy_array, Iter_enemy, &nr_of_enemies_now, &destroyed_enemies, explosion_array, m_explosion);
				info_nr = 4;
				break;
			case 1:
				powerup_array[iterator_1]->Helmet(m_player, proj_array, Iter);
				info_nr = 5;
				break;
			case 2:
				powerup_array[iterator_1]->Shovel(Iter_wall, wall_array, base_walls);
				info_nr = 6;
				break;
			case 3:
				powerup_array[iterator_1]->Star(m_player);
				info_nr = 7;
				break;
			case 4:
				powerup_array[iterator_1]->Tank(m_player);
				hp_status + 1;
				info_nr = 8;
				break;
			case 5:
				powerup_array[iterator_1]->Timer(enemy_array, Iter_enemy);
				info_nr = 9;
				break;
			}
			text = new ShowText(m_ptr, info_nr); //display information about the bonus
			text->Initialization();
			text->SetTextPosition(view.getCenter());
			text_array.push_back(text);
		}
		iterator_1++;
	}
}

#pragma endregion