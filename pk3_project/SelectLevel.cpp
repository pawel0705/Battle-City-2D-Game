#include "SelectLevel.h"

#pragma region Constructors

SelectLevel::SelectLevel(GameReference m_ptr) : m_ptr(m_ptr)
{
	m_ptr->fontManager.LoadAsset("Modia", "fonts/Modia.otf"); //load font from file
}

#pragma endregion

#pragma region Class methods

void SelectLevel::Updating(double deltaTime)
{
	sf::Event event; //update the event window

	while (m_ptr->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) //if you clicked the red cross, turn off the window
		{
			m_ptr->m_window.close();
		}
	}

	sf::Time elapsed = select_clock.getElapsedTime();

	if (elapsed.asSeconds() > 0.1f) //wait 0.1 seconds between switching to the appropriate options
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //go to the bottom of the list
		{
			iterator_2++;
			if (iterator_2 > iterator_1)
			{
				iterator_2 = 0;
			}
			maps[iterator_2].setFillColor(sf::Color::Green);
			maps[iterator_2 - 1].setFillColor(sf::Color::White);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //go to the top of the list
		{
			iterator_2--;
			if (iterator_2 < 0)
			{
				iterator_2 = iterator_1;
				maps[0].setFillColor(sf::Color::White);
			}
			else
			{
				maps[iterator_2 + 1].setFillColor(sf::Color::White);
			}
			maps[iterator_2].setFillColor(sf::Color::Green);
		}
		select_clock.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Confirm the selection of the map
	{
		map_name_tmp = maps[iterator_2].getString();
		if (map_name_tmp == "")
		{
			return;
		}
		m_ptr->m_stateMachine.AddNewState(std::unique_ptr<ProgramState>(new GameLoop(map_name_tmp, m_ptr))); //go to the game
	}
}

void SelectLevel::Initialization()
{
	std::ifstream loadfile("maps_file.dat", std::ios_base::binary); //read the map names from the file
	if (loadfile.good())
	{
		while (true)
		{
			std::getline(loadfile, test, '\0'); //read the names until you encounter the end of the word
			if (loadfile.eof())
			{
				break;
			}
			maps[iterator_1].setString(test);
			maps[iterator_1].setFont(m_ptr->fontManager.GetAsset("Modia"));
			maps[iterator_1].setPosition(sf::Vector2f((WIDTH / 2) - test.size() * 10, (HEIGHT / MAX + iterator_1 * SIZE) - HEIGHT/4)); //set the text positions
			iterator_1++;
		}
	}
	maps[0].setFillColor(sf::Color::Green);
}

void SelectLevel::Drawing(double deltaTime)
{
	for (int i = 0; i < iterator_1; i++)
	{
		m_ptr->m_window.draw(maps[i]); //draw all texts
	}
}

void SelectLevel::Input()
{
	
}

#pragma endregion