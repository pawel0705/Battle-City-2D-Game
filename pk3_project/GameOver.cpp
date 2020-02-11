#include "GameOver.h"

#pragma region Constructors

GameOver::GameOver(Points score, NoKilled nr_enemies_killed, GameReference ptr)
	: statistics(score),
	nr_enemies_killed(nr_enemies_killed),
	m_ptr(ptr)
{}

#pragma endregion

#pragma region  Class methods

void GameOver::Initialization() //load textures, fonts and set subtitles
{
	m_ptr->textureManager.LoadAsset("game_over", "textures/game_over.png");
	m_background.setTexture(m_ptr->textureManager.GetAsset("game_over"));

	score_text.setFont(m_ptr->fontManager.GetAsset("Modia"));
	score_text.setString("  YOUR SCORE: " + std::to_string(statistics.score));
	score_text.setCharacterSize(50);
	score_text.setFillColor(sf::Color::White);
	score_text.setOrigin(sf::Vector2f(score_text.getGlobalBounds().width / 2, score_text.getGlobalBounds().height / 2));
	score_text.setPosition(sf::Vector2f(m_ptr->m_window.getSize().x /2, m_ptr->m_window.getSize().y / 2));

	nr_enemies_killed_text.setFont(m_ptr->fontManager.GetAsset("Modia"));
	nr_enemies_killed_text.setString("ENEMIES KILLED: " + std::to_string(nr_enemies_killed.nr_enemies_killed));
	nr_enemies_killed_text.setCharacterSize(50);
	nr_enemies_killed_text.setFillColor(sf::Color::White);
	nr_enemies_killed_text.setOrigin(sf::Vector2f(score_text.getGlobalBounds().width / 2, score_text.getGlobalBounds().height / 2));
	nr_enemies_killed_text.setPosition(sf::Vector2f(m_ptr->m_window.getSize().x / 2, m_ptr->m_window.getSize().y / 2 + 64));

	ReadHighscore();

	high_score_text.setFont(m_ptr->fontManager.GetAsset("Modia"));
	high_score_text.setString("HIGH SCORE: " + std::to_string(high_score));
	high_score_text.setCharacterSize(50);
	high_score_text.setFillColor(sf::Color::White);
	high_score_text.setOrigin(sf::Vector2f(high_score_text.getGlobalBounds().width / 2, high_score_text.getGlobalBounds().height / 2));
	high_score_text.setPosition(sf::Vector2f(m_ptr->m_window.getSize().x / 2, m_ptr->m_window.getSize().y / 2 + 128));

	if (new_high_score == true) //if a new record has been reached, join the word "new"
	{
		high_score_text.setString("HIGH SCORE: " + std::to_string(high_score) + " NEW!");
	}
}

void GameOver::Input()
{
	sf::Event event; //check the event with what happens to the window

	while (m_ptr->m_window.pollEvent(event)) 
	{
		if (sf::Event::Closed == event.type)
		{
			m_ptr->m_window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //if the player presses "enter", exit to the main menu
		{
			m_ptr->m_stateMachine.AddNewState(StateReference(new MainMenu(m_ptr)));
		}
	}
}

void GameOver::Updating(double deltaTime)
{
	//nothing here
}

void GameOver::Drawing(double deltaTime) //draw textures and text
{
	m_ptr->m_window.draw(m_background);
	m_ptr->m_window.draw(score_text);
	m_ptr->m_window.draw(nr_enemies_killed_text);
	m_ptr->m_window.draw(high_score_text);
}

void GameOver::ReadHighscore()
{
	std::ifstream file("high_score.bin", std::ios::binary); //read high score
	if (file.is_open())
	{
		file.read((char*)&high_score, sizeof(int));
	}

	if ((high_score < statistics.score) || !file.is_open()) //if it's a new high score, replace it instead of the old one
	{
		high_score = statistics.score;
		new_high_score = true;
		SaveHighscore();
	}
	file.close();
}

void GameOver::SaveHighscore() //save the new high score to the file
{
	std::ofstream file("high_score.bin", std::ios::binary);
	file.write(reinterpret_cast<const char *>(&statistics.score), sizeof(int));
	file.close();
}

#pragma endregion