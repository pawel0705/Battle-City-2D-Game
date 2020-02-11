#ifndef Sprite_hpp
#define Sprite_hpp

#include <SFML/Graphics.hpp>

#include <vector>

class Sprite //class that stores information about sprite
{
private:
	std::vector<sf::IntRect> frame; //farame 
	const sf::Texture *texture = nullptr; //texture indicator

protected:
	sf::Sprite tank_sprite; 
	sf::RectangleShape tank_rectangle;

public:
	Sprite();
	~Sprite() = default;

	void addNextFrame(sf::IntRect rectangle); //add another frame

	void SetRectanglePosition(const sf::Vector2f & position); //accessors
	void SetSpriteSheet(const sf::Texture& texture);

	const sf::Texture* GetSpriteSheet() const;
	int GetSize() const;
	sf::RectangleShape GetRectangle() const;
	const sf::IntRect& GetFrame(int frame) const;
};

#endif
