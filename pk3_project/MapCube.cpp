#include "MapCube.h"

#pragma region Constructors

MapCube::MapCube(GameReference m_ptr) //calling constructors and setting appropriate variables depending on the initialized block
{
	this->m_ptr = m_ptr;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, bool brick_CanShoot)
{
	this->m_ptr = m_ptr;
	this->brick_canShoot = brick_CanShoot;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy)
{
	this->m_ptr = m_ptr;
	this->brick_heal = brick_heal;
	this->brick_canDestroy = brick_canDestroy;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, bool brick_canDrive, bool brick_canShoot)
{
	this->m_ptr = m_ptr;
	this->brick_CanDrive = brick_canDrive;
	this->brick_canShoot = brick_canShoot;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy, bool isBaseWalls)
{
	this->m_ptr = m_ptr;
	this->brick_heal = brick_heal;
	this->brick_canDestroy = brick_canDestroy;
	this->isBaseWalls = isBaseWalls;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, int brick_heal, bool brick_canDestroy, bool isBase, bool isBaseAlive)
{

	this->m_ptr = m_ptr;
	this->brick_heal = brick_heal;
	this->brick_canDestroy = brick_canDestroy;
	this->isBase = isBase;
	this->isBaseAlive = isBaseAlive;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, bool brick_CanDrive, bool is_enemy_spawn_point, bool brick_canShoot)
{
	this->m_ptr = m_ptr;
	this->brick_CanDrive = brick_CanDrive;
	this->is_enemy_spawn_point = is_enemy_spawn_point;
	this->brick_canShoot = brick_canShoot;

	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));
}

MapCube::MapCube(GameReference m_ptr, int brick_heal, bool brick_canDrive, bool brick_canShoot, bool brick_is_destroyed, bool is_enemy_spawn_point, bool isBase, bool isBaseAlive, bool brick_canDestroy)
{
	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));

	this->brick_heal = brick_heal;
	this->brick_canDestroy = brick_canDestroy;
	this->brick_CanDrive = brick_canDrive;
	this->brick_canShoot = brick_canShoot;
	this->brick_is_destroyed = brick_is_destroyed;
	this->is_enemy_spawn_point = is_enemy_spawn_point;
	this->isBase = isBase;
	this->isBaseAlive = isBaseAlive;
	this->m_ptr = m_ptr;
}

MapCube::MapCube(int type_of_brick, GameReference m_ptr)
{
	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	brick_rectangle.setSize(sf::Vector2f(64, 64));
	brick_rectangle.setFillColor(sf::Color(0, 0, 0, 0));

	this->m_ptr = m_ptr;
	this->type_of_brick = type_of_brick;
}

MapCube::~MapCube() {}

#pragma endregion

#pragma region Class methods

void MapCube::Drawing(double deltaTime)
{
	brick_sprite.setPosition(brick_rectangle.getPosition()); //draw block
}

#pragma endregion

#pragma region Accessors

void MapCube::SetisDestroyed(bool isDestroyed)
{
	this->brick_is_destroyed = isDestroyed; //set the status of destruction
}

void MapCube::SetHP(int HP)
{
	this->brick_heal = HP; //set the number of life points
}

void MapCube::SetCanDestroy(bool CanDestroy)
{
	this->brick_canDestroy = CanDestroy; //set whether you can destroy the block
}

void MapCube::SetIsEnemySpawnPoint(bool is_enemy_spawn_point)
{
	this->is_enemy_spawn_point = is_enemy_spawn_point; //set the opponent's spawn point
}

void MapCube::SetIsCollidable(bool brick_CanDrive)
{
	this->brick_CanDrive = brick_CanDrive; //set the collision
}

void MapCube::SetIsBase(bool isBase)
{
	this->isBase = isBase; //set the status of the base
}

void MapCube::SetRectanglePosition(float x, float y)
{
	brick_rectangle.setPosition(x, y); //set x, y
}

void MapCube::SetTextureSprite(const sf::Texture & texture, const sf::IntRect & rectangle)
{
	brick_sprite.setTexture(texture); //set texture and sprite
	brick_sprite.setTextureRect(rectangle);
}

int MapCube::GetHP() const
{
	return this->brick_heal; //get health points of brick
}

bool MapCube::GetisDestroyed() const
{
	return this->brick_is_destroyed; //get destroyed status
}

bool MapCube::GetCanDestroy() const
{
	return this->brick_canDestroy; //take information if the wall can be destroyed
}

bool MapCube::GetisEnemySpawnPoint() const
{
	return this->is_enemy_spawn_point; //take information if this is spawn opponents
}

bool MapCube::GetisCollidable() const
{
	return this->brick_CanDrive; //get information if you can cross this wall
}

bool MapCube::GetIsBase() const
{
	return this->isBase; //get information if it's a base
}

bool MapCube::GetCanShotThrough() const
{
	return this->brick_canShoot; //get information if you can shoot through this wall
}

bool MapCube::GetIsBaseWalls() const
{
	return this->isBaseWalls; //get information whether these are walls belonging to the base
}

sf::RectangleShape MapCube::GetRectangle() const
{
	return this->brick_rectangle; //get rectangle
}

sf::Sprite MapCube::GetSprite() const
{
	return this->brick_sprite; //get sprite
}

int MapCube::GetTypeOfbrick() const
{
	return this->type_of_brick; //get type of brick
}

#pragma endregion
