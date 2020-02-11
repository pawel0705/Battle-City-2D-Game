#ifndef NoKilled_hpp
#define NoKilled_hpp

#include "HUD.h"

class NoKilled : public HUD //amount of destroyed opponents
{
public:
	int nr_enemies_killed = 0;

	NoKilled(const std::string & text, const int & characterSize, const sf::Vector2f & position, const sf::Font & font)
		: HUD(text, characterSize, position, font)
	{}
	NoKilled()
	{}

	NoKilled operator++(int);
};

#endif