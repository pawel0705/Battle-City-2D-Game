#include "Sprite.h"

#pragma region Constructors

Sprite::Sprite() {}

#pragma endregion

#pragma region Class methods

void Sprite::addNextFrame(sf::IntRect rectangle)
{
	this->frame.push_back(rectangle); //add a new animation frame to the container
}

#pragma endregion

#pragma region Accesors

void Sprite::SetSpriteSheet(const sf::Texture& texture)
{
	this->texture = &texture; //set sprite sheet
}

void Sprite::SetRectanglePosition(const sf::Vector2f & position)
{
	this->tank_rectangle.setPosition(position); //set position of rectangle
}

const sf::Texture* Sprite::GetSpriteSheet() const
{
	return this->texture; //return the texture
}

sf::RectangleShape Sprite::GetRectangle() const
{
	return this->tank_rectangle; //return the rectangle
}

int Sprite::GetSize() const
{
	return this->frame.size(); //return the sprite size
}

const sf::IntRect& Sprite::GetFrame(int frame) const
{
	return this->frame[frame]; //Return the frame of the animation
}

#pragma endregion