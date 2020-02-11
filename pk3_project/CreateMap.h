#ifndef CreateMap_hpp
#define CreateMap_hpp

#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include <iostream>

#include "MapCube.h"
#include "AssetManager.h"
#include "ProgramState.h"
#include "MainMenu.h"

class CreateMap : public ProgramState //The class responsible for crating map by player (custom map)
{
	std::vector<MapCube> square; //storage of walls
	std::vector<MapCube>::const_iterator Iter_wall; //iterator for vector

	GameReference m_ptr; //smart indicator (state machine)

	int max_x = 0; //maximum range of block position (how far the player has put a block counting from 0.0 [upper left corner])
	int max_y = 0;
	int iterator_1 = 0; //helping iterator
	int block_counter = 0; //how many blocks
	int created_map[19][11]; //the maximum size of the custom map

	bool pressed_spacebar = false; //if player pressed spacebar
	bool decision = false; //whether the player has approved the block
	std::string string_tmp; //temporaty string

	sf::Sprite sprite;
	sf::RectangleShape rectangle;
	sf::Clock key_clock; //clock preventing from spamming keyboards
	sf::Clock moving_clock; //clock that slow down the jump between blocks

public:
	CreateMap();
	CreateMap(GameReference m_ptr);
	~CreateMap() = default;

	template<typename T, int height, int width>
	std::ostream& writemap(std::ostream& os, T(&map)[height][width]); //write map to file

	void SaveMap(); //savig player's map

	virtual void Updating(double deltaTime) override; //updating map
	virtual void Input() override; //input keyboard
	virtual void Drawing(double DeltaTime) override; //show on screen
	virtual void Initialization() override; //prepare data
};

#endif