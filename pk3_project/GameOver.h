#ifndef GameOver_hpp
#define GameOver_hpp

#include <SFML/Graphics.hpp>

#include "ProgramState.h"
#include "GameAssets.h"
#include "Points.h"
#include "NoKilled.h"
#include "MainMenu.h"

class GameOver : public ProgramState , public Points, public NoKilled //the class responsible for the results table
{
	Points statistics; //number of points
	NoKilled nr_enemies_killed; //number of destroyed opponents

	GameReference m_ptr; //pointer on the state of the game (state machine)

	int score; //number of points
	int enemies_killed; //number of destroyed opponents
	int high_score; //high score
	int tmp_score; //auxiliary variable to help transfer points between variables
	bool new_high_score = false;

	sf::Sprite m_background;
	sf::Text score_text;
	sf::Text nr_enemies_killed_text;
	sf::Text high_score_text;

public:
	GameOver(Points score, NoKilled enemies_killed, GameReference ptr);

	void Initialization() override; //load basic data
	void Input() override; //input
	void Updating(double deltaTime) override; //update state
	void Drawing(double deltaTime) override; //draw table

	void SaveHighscore(); //save new high score
	void ReadHighscore(); //read high score
};
#endif