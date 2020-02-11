#ifndef HUD_hpp
#define HUD_hpp

#include "SFML/Graphics.hpp"
#include <string>

class HUD : public sf::Transformable, public sf::Drawable //base class responsible for displaying hud
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Text text;

public:
	HUD(const std::string& text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font);

	HUD()
	{}
};

#endif