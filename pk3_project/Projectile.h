#ifndef Projectile_hpp
#define Projectile_hpp

#include "ProgramState.h"
#include "GameAssets.h"

class Projectile //class responsible for the description of the projectile
{
	int proj_dmg = 0; //bullet damage
	int projectile_speed = 200; //projectile speed
	int projectile_direction = 1; //he position in which the missile is to fly
	int counter_life = 0; //how long the bullet is alive
	int proj_lifetime =100; //after what time the missile is to be destroyed
	int projectile_status = NEUTRAL; //the status of the projectile

	bool destroyed = false; //if the missile was destroyed

	enum projectile_status
	{
		NEUTRAL = 0, //it can destroy only a wall
		PLAYER = 1, //the bullet belongs to the player
		ENEMY = 2 //the missile belongs to the opponent
	};

	GameReference m_ptr; //smart pointer to assets

	sf::RectangleShape projectile_rectangle;
	sf::Sprite projectile_sprite;

public:
	Projectile(GameReference ptr);
	~Projectile();

	Projectile & operator *=(const int & x);

	void Updating(double deltaTime); //updating projectile
	void Drawing(double deltaTime); //draw projectile

	void SetDirection(int projectile_direction); //accesors
	void SetProjectileStatus(int);
	void SetDestroyed(bool destroyed);
	void SetRectanglePosition(float x, float y);

	int GetProjectileStatus() const;
	bool GetDestroyed() const;
	sf::RectangleShape GetRectangle() const;
};

#endif