#ifndef SelectLevel_hpp
#define SelectLevel_hpp

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include "ProgramState.h"
#include "AssetManager.h"
#include "GameAssets.h"
#include "Settings.h"
#include "GameLoop.h"

class SelectLevel : public ProgramState //choosing a map from the list
{
	int iterator_1 = 0;
	int iterator_2 = 0;

	std::string test;
	std::string map_name_tmp; //name of map

	GameReference m_ptr; //smart pointer to assets

	sf::Text maps[10];
	sf::Clock select_clock;

public:
	SelectLevel(GameReference m_ptr);
	SelectLevel() = default;
	~SelectLevel() = default;

	void Initialization() override; //load basic data
	void Input() override; //input from keyboard
	void Updating(double deltaTime) override; //update
	void Drawing(double deltaTime) override; //draw
};

#endif