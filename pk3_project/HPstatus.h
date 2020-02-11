#ifndef HPstatus_hpp
#define HPstatus_hpp

#include "HUD.h"
#include "Enemy.h"

class HPstatus : public HUD //the class responsible for showing the player's state of life
{
	int hp_max = 0; //max hp
	int hp_now = 0; //actual hp
	int lives = 0; //player's lives

public:
	HPstatus(const std::string& text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font)
		:HUD(text, characterSize, position, font)
	{}
	HPstatus()
	{}

	void GetPlayerMaxHP(int, int);
	int operator-(const Enemy & enemy);

	HPstatus & operator++();
	HPstatus & operator+(int);
};

#endif