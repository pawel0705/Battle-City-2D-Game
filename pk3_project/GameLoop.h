#ifndef GameLoop_hpp
#define GameLoop_hpp

#include <SFML/Graphics.hpp>

#include <iostream>

#include "ProgramState.h"
#include "Game.h"
#include "StateMachine.h"
#include "Settings.h"
#include "Player.h"
#include "Projectile.h"
#include "MapFile.h"
#include "MapCube.h"
#include "Enemy.h"
#include "Points.h"
#include "GameOver.h"
#include "NoKilled.h"
#include "Explosion.h"
#include "HPstatus.h"
#include "Powerup.h"
#include "ShowText.h"


class GameLoop : public ProgramState //The class that looped the game
{
	GameReference m_ptr; //pointer to gamereference

	class Player *m_player = nullptr; //player
	class Enemy *m_enemy = nullptr; //enemy
	class Projectile *m_bullet = nullptr; //projectile
	class Explosion *m_explosion = nullptr; //explosion
	class Powerup *m_powerup = nullptr; //bonus
	class ShowText *text = nullptr; //text

	std::vector<Powerup*> powerup_array; //containers and their iterators for the indicators declared above
	std::vector<Powerup*>::const_iterator iter_powerup;
	std::vector<Enemy*> enemy_array;
	std::vector<Enemy*>::const_iterator Iter_enemy;
	std::vector<Projectile*>::const_iterator Iter;
	std::vector<Projectile*> proj_array;
	std::vector<MapCube>::const_iterator Iter_wall, Iter_wall_2;
	std::vector<MapCube> wall_array;
	std::vector<MapCube> base_walls;
	std::vector<Explosion*> explosion_array;
	std::vector<Explosion*>::const_iterator Iter_explosion;
	std::vector<ShowText*> text_array;
	std::vector<ShowText*>::const_iterator iter_text;

	//-----ITERATORS -----//
	int iterator_1 = 0, iterator_2 = 0;
	int nr_base_array = 0;
	
	//-----TMP VARIABLES-----//
	int tmp_i = 0;
	bool tmp_bool = false;
	sf::RectangleShape tmp_rectangle;
	std::string string_tmp = "null";
	int sizeX, sizeY;
	int info_nr = 0;
	float X_last_position = 0;
	float Y_last_position = 0;
	bool remember_X = false;
	bool remember_Y = false;

	//-----HUD----//
	Points hud; //points
	NoKilled nr_enemies; //amount of destroyed opponents
	HPstatus hp_status; //amount of life

	bool end_game = false;
	bool game_over = false;
	bool draw_hud = true;
	int spawned_enemies = 0; //amount of spawned opponents
	int nr_of_enemies_now = 0; //current number of enemies on the map
	int max_enemies = 10; //the number of enemies required for destruction to complete the game
	int destroyed_enemies = 0; //the amount of destroyed opponents by the player
	sf::Vector2f enemy_spawn_position; //storage of enemy spawn coordinates

	sf::Sprite Sprite_Ground;
	sf::Sprite Game_border;
	sf::RectangleShape spawn_point_rectangle;
	sf::Clock generate_powerup;
	sf::Clock wait_to_score_state; //wait a few seconds after completing the end of game condition to move on
	sf::Font font;
	sf::View view; //camera

public:
	GameLoop(std::string string_tmp, GameReference ptr);
	~GameLoop();

	void Initialization() override; //load basic data
	void Input() override; //input
	void Updating(double deltaTime) override; //updating all objects
	void Drawing(double deltaTime) override; //draw all objects

	void isOver(); //whether the game ended
	void Deleting(); //removing unnecessary objects
	void SpawnPowerUp(); //spawning bonuses for the player
	void Collision(); //collision check
	void CameraUpdate(); //moving the camera
};

#endif