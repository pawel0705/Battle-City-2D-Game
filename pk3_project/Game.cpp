#include "Game.h"

#pragma region Constructors

Game::Game()
{
	m_ptr->fontManager.LoadAsset("Modia", "fonts/Modia.otf"); //load font
	framesPerSecond.setFont(m_ptr->fontManager.GetAsset("Modia")); //set font
	framesPerSecond.setFillColor(sf::Color::Green); //set green color on text
	m_ptr->m_window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Titlebar | sf::Style::Close); //video mode 1280x720, can't resize
	m_ptr->m_stateMachine.AddNewState(StateReference(new MainMenu(this->m_ptr))); //go to main menu state
}

Game::~Game() 
{}

#pragma endregion

#pragma region  Class methods

void Game::showFPS(float deltaTime) //show fps on screen
{
	int m_fps = 1.0f / (deltaTime);
	std::ostringstream tmp;
	tmp << m_fps;
	framesPerSecond.setString(tmp.str() + "FPS"); //update text
	framesPerSecond.setPosition(m_ptr->m_window.getView().getCenter().x - WIDTH / 2, m_ptr->m_window.getView().getCenter().y - HEIGHT / 2);
	m_ptr->m_window.draw(framesPerSecond); //draw fps on screen
}

void Game::RunGame()
{
	while (m_ptr->m_window.isOpen())
	{
		this->m_ptr->m_stateMachine.ChangingState(); //check state in statne machine
		while (accumulator > update_s) //update delta time
		{
			accumulator -= update_s;
			sec = update_s.asSeconds();
			m_ptr->m_stateMachine.GetCurrentState()->Input(); //input function
			m_ptr->m_stateMachine.GetCurrentState()->Updating(sec); //updating function
		}
		this->m_ptr->m_stateMachine.ChangingState(); //check state in statne machine

		m_ptr->m_window.clear(); //clear window
		m_ptr->m_stateMachine.GetCurrentState()->Drawing(sec); //drawing functions 
		showFPS(sec);
		m_ptr->m_window.display(); //display

		accumulator += m_clock.restart(); //update time
	}
}

#pragma endregion