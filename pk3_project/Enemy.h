#ifndef Enemy_hpp
#define Enemy_hpp

#include "ProgramState.h"
#include "GameAssets.h"
#include "Tank.h"
#include "Sprite.h"

#include "Animation.h"

#include <random>
#include <chrono>
#include <functional>

class Enemy : public Tank, public Sprite, public ProgramState //Class that stores information and behavior of the opponent, inherits from 3 classes
{
	int enemy_direction_length = 0; //how far it travels one way after making a decision about moving
	int hammer_length = 0; //the length of the animation of the appearance of the opponent
	int enemy_speed = 100; //opponent's speed
	int hammer_elapsed = 0; //how much the animation of the opponent's appearance has been looped

	bool chasing_player = false; //if the opponent chases the player
	bool destroying_base = false; //whether the opponent is destroying the base
	bool what_to_do = false; //does the opponent know what to do?
	bool freeze = false; //if "true" then the opponent can not take any action
	bool show_enemy = false; //an auxiliary variable to draw the initial frame of the animation

	GameReference m_ptr; //smart pointer on the state of the game/game assets (state machine)

	sf::Sprite spawning_sprite; 
	sf::Sprite timer_sprite;
	sf::RectangleShape enemy_view; //view range of the opponent
	sf::RectangleShape base_rectangle; //storing the coordinates of the base so that the opponent knows where base is
	sf::RectangleShape player_rectangle; //storing the player coordinates so that the opponent knows where he is
	sf::Clock shooting_clock; //a timer that prevents the opponent from firing as if from a laser
	sf::Clock stop_time_clock;

	Sprite* actual_animation = nullptr; //** Sprite animations **//
	Sprite Down, Left, Right, Up; 
	Animation moving_sprite;
	sf::Clock clock_frame;

public:
	Enemy();
	Enemy(sf::RectangleShape base_rectangle, GameReference ptr);
	~Enemy();

	Enemy & operator=(const Enemy & enemy) noexcept; //assignment operator for the opponent

	void Algorithm(sf::RectangleShape player_rectangle); //some smart enemy behavior

	void Initialization() override; //loading of preliminary data
	void Input() override; //reading traffic decisions
	void Updating(double deltaTime) override; //updating enemy
	void Drawing(double deltaTime) override; //drawing enemy

	void StopTime(); //Stop the opponent if the player took the right bonus
	int Randomize(); //Random behavior
	void StopEnemy(int); //Stop the opponent
};

#endif