#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>

#include "GameAssets.h"
#include "ProgramState.h"
#include "Enemy.h"
#include "Tank.h"
#include "Explosion.h"
#include "Sprite.h"

class Player : public Tank, public Sprite, public ProgramState //class that stores information about the player
{
	int player_hp = 100; //the number of player points
	int life = 3; //number of player lives
	int tier_level = DEFAULT; //tier player level (level)
	int bullet_multipler = DEFAULT; //how much time the player can shoot bullets

	float fire_speed = 1.5f; //time interval between shots
	double player_speed = 100; //player's speed of movement

	bool already_exploding = false; //whether the player is exploding
	bool two_bollets = false; //whether the player can shoot more missiles in a shorter period of time
	bool player_collision = false; //whether the player is interfering with something
	bool shield_active = true; //is the anti-missile shield active
	bool show_player = false; //an auxiliary variable to draw the initial frame of the animation

	enum tier //an enumeration variable responsible for tiers
	{
		DEFAULT = 1,
		SECOND = 2,
		THIRD = 3,
		FOURTH = 4
	};

	GameReference m_ptr; //smart pointer on the state of the game/game assets (state machine)

	sf::Clock projectile_clock;
	sf::Clock shield_clock;
	sf::Sprite shield_sprite;

	Sprite* actual_animation = nullptr; //** Sprite animations **//
	Sprite Down, Left, Right, Up;
	Animation moving_sprite;
	sf::Clock clock_frame;
	
public:
	Player(GameReference ptr, int life);
	~Player();

	Player & operator=(const Player & tmp_player); //overloaded operators (what they do is described in the .cpp file)
	Player & operator++();
	Player operator++(int);
	Player & operator--();
	void operator() (int a, int b);
	int operator-(const Enemy & enemy);
	
	 virtual void Updating(double deltaTime) override; //updating player
	 virtual void Input() override; //input from keyboard
	 virtual void Drawing(double DeltaTime) override; //draw player
	 virtual void Initialization() override; //load basic data about player
	 
	 void StopPlayer(int e_direction); //stop player
	 void Tier(); //check tier

	 void SetPlayerCollision(bool player_collision); //accessors
	 void SetRectangle(sf::RectangleShape player_rectangle);
	 void SetShieldStatus(bool shield_active);

	 bool GetPlayerCollision() const;
	 int GetPlayerHP() const;
	 bool GetShieldStatus() const;
	 int GetMultipler() const;
	 int GetLife() const;
};

#endif