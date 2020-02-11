#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "GameAssets.h"
#include "Settings.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "GameLoop.h"

class Game //main class that synchronizes the game
{
	double sec = 0.0f; //a comma variable to determine the time course

	sf::Text framesPerSecond; //text to display fps
	sf::Clock m_clock;
	sf::Time accumulator; //storing time
	sf::Time update_s = sf::seconds(FPS);

public:
	Game();
	~Game();

	void showFPS(float deltaTime); //show fps
	void RunGame(); //run game

	GameReference m_ptr = std::make_shared<GameAssets>(); //smart pointer to assets
};
#endif