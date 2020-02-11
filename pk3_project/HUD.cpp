#include "HUD.h"

#pragma region Constructors

HUD::HUD(const std::string& text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font)
{
	this->text = sf::Text(text, font); //set the initial values of the text to be displayed
	this->text.setCharacterSize(characterSize);
	this->text.setFillColor(sf::Color::Yellow);
	this->text.setPosition(position);
}

#pragma endregion

#pragma region Class methods

void HUD::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const //draw text on screen (virtual function)
{
	render_states.transform *= getTransform();
	render_target.draw(text, render_states);
}

#pragma endregion