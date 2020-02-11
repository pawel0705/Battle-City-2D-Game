#ifndef MapCube_hpp
#define MapCube_hpp

#include <SFML/Graphics.hpp>

#include "ProgramState.h"
#include "GameAssets.h"

class MapCube  //class that stores block information
{
	int brick_heal = 0; //block life
	int type_of_brick = NOTHING; //block type

	bool brick_canDestroy = false; //variables inform (as the name suggests) what can be done with a given block
	bool brick_CanDrive = false;
	bool brick_canShoot = false;
	bool brick_is_destroyed = false;
	bool is_enemy_spawn_point = false;
	bool isBase = false;
	bool isBaseAlive = true;
	bool isBaseWalls = false;

	enum what_brick //an enumeration type helpful in determining the block type
	{
		NOTHING = 0,
		NORMAL_ROCK = 1,
		HARDER_ROCK = 2,
		WATER = 3,
		BUSH = 4,
		BAD_ROCK = 5,
		YOUR_BASE = 6,
		SPAWN_POINT = 7,
		ENEMY_SPAWN_POINT = 8,
		BASE_ROCK = 9
	};

	GameReference m_ptr; //smart pointer to game assets

	sf::RectangleShape brick_rectangle;
	sf::Sprite brick_sprite;

public:
	MapCube(GameReference m_ptr); //constructor for each type of block
	MapCube(GameReference m_ptr, bool brick_CanShoot);
	MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy);
	MapCube(GameReference m_ptr, bool brick_CanDrive, bool Brick_canShoot);
	MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy, bool isBaseWalls);
	MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy, bool isBase, bool isBaseAlive);
	MapCube(GameReference m_ptr, bool brick_CanDrive, bool is_enemy_spawn_point, bool brick_canShoot);
	MapCube(GameReference m_ptr, int brick_heal, bool brick_canDrive, bool brick_canShoot, bool brick_is_destroyed, bool is_enemy_spawn_point, bool isBase, bool isBaseAlive, bool brick_canDestroy);
	MapCube(int type_of_brick, GameReference m_ptr);
	~MapCube();

	void Drawing(double deltaTime); //drawing block
	
	void SetisDestroyed(bool); //accessors
	void SetHP(int);
	void SetCanDestroy(bool);
	void SetIsEnemySpawnPoint(bool);
	void SetIsCollidable(bool);
	void SetIsBase(bool);
	void SetRectanglePosition(float x, float y);
	void SetTextureSprite(const sf::Texture & texture, const sf::IntRect & rectangle);

	int GetHP() const;
	int GetTypeOfbrick() const;
	bool GetisDestroyed() const;
	bool GetCanDestroy() const;
	bool GetisEnemySpawnPoint() const;
	bool GetisCollidable() const;
	bool GetIsBase() const;
	bool GetCanShotThrough() const;
	bool GetIsBaseWalls() const;
	sf::RectangleShape GetRectangle() const;
	sf::Sprite GetSprite() const;
};

#endif