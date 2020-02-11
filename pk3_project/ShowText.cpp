#include "ShowText.h"

#pragma region Constructors

ShowText::ShowText(GameReference m_ptr, int communicate_noumber)
	:m_ptr(m_ptr), communicate_noumber(communicate_noumber)
{}

#pragma endregion

#pragma region Class methods

void ShowText::Initialization()
{
	m_ptr->fontManager.LoadAsset("Modia", "fonts/Modia.otf"); //load font from file

	for (int i = 0; i < 10; i++) //set basic properties
	{
		communicates[i].setFont(m_ptr->fontManager.GetAsset("Modia"));
		communicates[i].setCharacterSize(50);
		communicates[i].setStyle(sf::Text::Bold);
	}

	communicates[0].setFillColor(sf::Color::Red); //Entering appropriate messages to the tables
	communicates[0].setString("NULL");

	communicates[1].setFillColor(sf::Color::Red);
	communicates[1].setString("Your tank is a wreck!");

	communicates[2].setFillColor(sf::Color::Red);
	communicates[2].setString("Your base has been destroyed!");

	communicates[3].setFillColor(sf::Color::Green);
	communicates[3].setString("You killed all enemies!\n       You won!");

	communicates[4].setFillColor(sf::Color::Yellow);
	communicates[4].setString("Boom! Opponents destroyed!");

	communicates[5].setFillColor(sf::Color::Yellow);
	communicates[5].setString("Shield up!");

	communicates[6].setFillColor(sf::Color::Yellow);
	communicates[6].setString("Repair of base walls!");

	communicates[7].setFillColor(sf::Color::Yellow);
	communicates[7].setString("Tier up!");

	communicates[8].setFillColor(sf::Color::Yellow);
	communicates[8].setString("An additional point of life!");

	communicates[9].setFillColor(sf::Color::Yellow);
	communicates[9].setString("Stop opponents!");
}

void ShowText::Input()
{ 
	//nothing here
}

void ShowText::Updating(double deltaTime)
{
	sf::Time elapsed = clock_text.getElapsedTime();

	if (elapsed.asSeconds() >= 5.0f) //display a message for 5 seconds, then set the information to be deleted
	{
		delete_text = true;
	}
}

void ShowText::Drawing(double deltaTime)
{
	this->m_ptr->m_window.draw(communicates[communicate_noumber]); //draw the appropriate message
}

#pragma endregion

#pragma region Accessors

void ShowText::SetTextPosition(sf::Vector2f rectangleposition)
{
	this->communicates[communicate_noumber].setPosition(rectangleposition.x - communicates[communicate_noumber].getGlobalBounds().width/2 - 128, rectangleposition.y - 300); //set the text in the middle
}

bool ShowText::GetDeleteText() const
{
	return this->delete_text; //return information if the text should be deleted
}

#pragma endregion