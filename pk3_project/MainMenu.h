#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <SFML/Graphics.hpp>

#include <iostream>

#include "ProgramState.h"
#include "Settings.h"
#include "GameAssets.h"
#include "StateMachine.h"
#include "AssetManager.h"
#include "CreateMap.h"
#include "SelectLevel.h"
#include "GameLoop.h"

class MainMenu : public ProgramState //main menu class
{
	int m_choice; //option number
	GameReference m_ptr; //smart pointer to game assets

	sf::Sprite sprites[8]; //an array of button sprites

public:
	MainMenu(GameReference ptr);
	~MainMenu();

	 void Initialization() override; //basic data
	 void Input() override; //input keys from keyboard
	 void Updating(double deltaTime) override; //updating state
	 void Drawing(double deltaTime) override; //draw state

	 void GoUp(); //go up
	 void GoDown(); //go down
	 int GetOption() const; //get option
};

#endif
