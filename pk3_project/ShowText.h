#ifndef ShowText_hpp
#define ShowText_hpp

#include "ProgramState.h"
#include "GameAssets.h"
#include "StateMachine.h"
#include "AssetManager.h"
#include "Settings.h"

class ShowText : public ProgramState //a class that stores messages that are displayed during the game
{
	int communicate_noumber = 0; //message number
	bool delete_text = false; //whether the message is to be deleted

	GameReference m_ptr; //smart pointer to assets

	sf::Text communicates[10]; //text table that stores messages
	sf::Clock clock_text; //the life of the text

public:
	ShowText(GameReference m_ptr, int comminicate_noumber);

	void Initialization() override; //load basic data
	void Input() override; //input
	void Updating(double deltaTime) override; //updating
	void Drawing(double deltaTime) override; //draw

	void SetTextPosition(sf::Vector2f rectangleposition); //accesors
	bool GetDeleteText() const;
};

#endif