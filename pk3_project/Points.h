#ifndef ActualHUD_hpp
#define ActualHUD_hpp

#include "HUD.h"

class Points : public HUD //class that stores the number of points scored by the player
{
public:
	int score = 0;

	Points(const std::string& text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font)
		:HUD(text, characterSize, position, font)
	{}
	Points()
	{}
	Points operator++(int);
	Points operator+(int);
};

#endif