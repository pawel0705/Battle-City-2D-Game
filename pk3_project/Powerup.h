#ifndef Powerup_hpp
#define Powerup_hpp

#include <SFML/Graphics.hpp>

#include <random>
#include <chrono>
#include <functional>

#include "GameAssets.h"
#include "ProgramState.h"
#include "Game.h"

class Powerup : public ProgramState //class that stores information and actions on powerups
{
	int bonus_type; //type of bonus
	int random = 0; //random noumber
	int iterator_1 = 0;
	int life_time = 550; //the duration of the bonus on the map
	int couneter_life = 0; //how long the bonus is on the map

	bool delete_powerup = false; //whether to remove the bonus

	enum power //an enumeration variable informing about the type of the bonus
	{
		GRENADE = 0,
		HELMET = 1,
		SHOVEL = 2,
		STAR = 3,
		TANK = 4,
		TIMER = 5
	};

	sf::RectangleShape powerup_rectangle;
	sf::Sprite powerup_sprite;
	GameReference m_ptr;  //smart pointer to game assets

public:
	Powerup(GameReference m_ptr);

	//functions that perform the actions depending on the bonus
	void Grenade(std::vector<Enemy*> &enemy_array, std::vector<Enemy*>::const_iterator &Iter_enemy, int *nr_of_enemies_now,  int *destroyed_enemies, std::vector<Explosion*> &explosion_array, Explosion *m_explosion);
	void Helmet(Player *player, std::vector<Projectile*> &projectile_array, std::vector<Projectile*>::const_iterator &iter_proj);
	void Shovel(std::vector<MapCube>::const_iterator &Iter_wall, std::vector<MapCube> &wall_array, std::vector<MapCube> &base_walls);
	void Timer(std::vector<Enemy*> &enemy_array, std::vector<Enemy*>::const_iterator &Iter_enemy);
	void Tank(Player *player);
	void Star(Player *player);

	void RandomisePosition(int x, int y); //drawing the position (where the bonus will appear)
	int Randomize(float from, float to); //draw a number from a given range (bonus type draw)

	void Updating(double deltaTime) override; //updating bonus
	void Input() override; //input
	void Drawing(double DeltaTime) override; //draw bonus
	void Initialization() override; //load basic data

	sf::RectangleShape GetRectangle() const; //accessors
	int GetPowerup() const;
	bool GetIsDeleted() const;

	void SetRectanglePosition(const sf::Vector2f & position);
};

#endif
