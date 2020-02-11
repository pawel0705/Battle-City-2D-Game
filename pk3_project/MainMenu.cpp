#include "MainMenu.h"

#pragma region Constructors

MainMenu::MainMenu(GameReference ptr) : m_ptr(ptr)
{
	m_ptr->fontManager.LoadAsset("Modia", "fonts/Modia.otf"); //load font and button images
	m_ptr->textureManager.LoadAsset("menu1", "textures/menu1.png");
	m_ptr->textureManager.LoadAsset("menu2", "textures/menu2.png");
	m_ptr->textureManager.LoadAsset("playgame", "textures/playgame.png");
	m_ptr->textureManager.LoadAsset("playgame_2", "textures/playgame_2.png");
	m_ptr->textureManager.LoadAsset("create_map", "textures/create_map.png");
	m_ptr->textureManager.LoadAsset("create_map2", "textures/create_map2.png");
	m_ptr->textureManager.LoadAsset("exit", "textures/exit.png");
	m_ptr->textureManager.LoadAsset("exit2", "textures/exit2.png");
}

MainMenu::~MainMenu() {}

#pragma endregion

#pragma region Class methods

void MainMenu::Updating(double deltaTime) 
{
	//nothing here
}

void MainMenu::Initialization()
{
	sprites[0].setTexture(m_ptr->textureManager.GetAsset("menu1")); //load the buttons to the array
	sprites[1].setTexture(m_ptr->textureManager.GetAsset("menu2"));
	sprites[2].setTexture(m_ptr->textureManager.GetAsset("playgame"));
	sprites[3].setTexture(m_ptr->textureManager.GetAsset("playgame_2"));
	sprites[4].setTexture(m_ptr->textureManager.GetAsset("create_map"));
	sprites[5].setTexture(m_ptr->textureManager.GetAsset("create_map2"));
	sprites[6].setTexture(m_ptr->textureManager.GetAsset("exit"));
	sprites[7].setTexture(m_ptr->textureManager.GetAsset("exit2"));

	//set the initial position of the buttons
	sprites[0].setPosition((WIDTH / 2) - sprites[0].getGlobalBounds().width / 2, sprites[0].getGlobalBounds().height / 2);
	sprites[1].setPosition((WIDTH / 2) - sprites[1].getGlobalBounds().width / 2, sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);

	sprites[3].setPosition((WIDTH / 2) - sprites[2].getGlobalBounds().width / 2, sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
	sprites[4].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
	sprites[6].setPosition((WIDTH / 2) - sprites[6].getGlobalBounds().width / 2, sprites[6].getGlobalBounds().height + sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);

	sprites[2].setPosition(-1000, -1000);
	sprites[5].setPosition(-1000, -1000);
	sprites[7].setPosition(-1000, -1000);

	m_choice = 0;
}

void MainMenu::Input()
{
	sf::Event event; //update the event windows

	while (m_ptr->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_ptr->m_window.close(); //if a red cross has been pressed
		}
	}

	switch (event.type) // move up and down depending on the clicked arrow
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			GoUp();
			break;
		case sf::Keyboard::Down:
			GoDown();
			break;
		case sf::Keyboard::Return:
			switch (GetOption())
			{
			case 0:
				m_ptr->m_stateMachine.AddNewState(std::unique_ptr<ProgramState>(new SelectLevel(m_ptr))); //go to the map selection state
				break;
			case 1:
				m_ptr->m_stateMachine.AddNewState(std::unique_ptr<ProgramState>(new CreateMap(m_ptr))); //go to the map creation state
				break;
			case 2:
				m_ptr->m_window.close(); //close window
				break;
			}
			break;
		}
		break;
	case sf::Event::Closed:
		m_ptr->m_window.close(); //close window
		break;
	}
}


void MainMenu::Drawing(double deltaTime)
{
	for (int i = 0; i < 8; i++)
	{
		m_ptr->m_window.draw(sprites[i]); //draw buttons
	}
}

void MainMenu::GoUp()
{
	if (m_choice - 1 >= 0) //set the appropriate buttons on the screen in the appropriate position
	{
		m_choice--;
		if (m_choice + 2 == 2)
		{
			sprites[3].setPosition((WIDTH / 2) - sprites[2].getGlobalBounds().width / 2, sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[2].setPosition(-1000, -1000);
			sprites[5].setPosition(-1000, -1000);
			sprites[4].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
		}
		else if (m_choice + 2 == 3)
		{
			sprites[6].setPosition((WIDTH / 2) - sprites[6].getGlobalBounds().width / 2, sprites[6].getGlobalBounds().height + sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[7].setPosition(-1000, -1000);
			sprites[4].setPosition(-1000, -1000);
			sprites[5].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
		}

		else if (m_choice + 2 == 4)
		{
			sprites[6].setPosition((WIDTH / 2) - sprites[6].getGlobalBounds().width / 2, sprites[6].getGlobalBounds().height + sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[7].setPosition(-1000, -1000);
			sprites[4].setPosition(-1000, -1000);
			sprites[5].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
		}
	}
}

void MainMenu::GoDown()
{
	if (m_choice + 1 < 3) //set the appropriate buttons on the screen in the appropriate position
	{
		m_choice++;
		if (m_choice + 2 == 2)
		{
			sprites[6].setPosition((WIDTH / 2) - sprites[2].getGlobalBounds().width / 2, sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
		}
		else if (m_choice + 2 == 3)
		{
			sprites[3].setPosition(-1000, -1000);
			sprites[2].setPosition((WIDTH / 2) - sprites[2].getGlobalBounds().width / 2, sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[5].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[4].setPosition(-1000, -1000);
		}
		else if (m_choice + 2 == 4)
		{
			sprites[5].setPosition(-1000, -1000);
			sprites[4].setPosition((WIDTH / 2) - sprites[4].getGlobalBounds().width / 2, sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
			sprites[6].setPosition(-1000, -1000);
			sprites[7].setPosition((WIDTH / 2) - sprites[6].getGlobalBounds().width / 2, sprites[6].getGlobalBounds().height + sprites[4].getGlobalBounds().height + sprites[2].getGlobalBounds().height + sprites[1].getGlobalBounds().height + sprites[0].getGlobalBounds().height);
		}
	}
}

#pragma endregion

#pragma region operators

int MainMenu::GetOption() const
{
	return this->m_choice; //return the option selection number
}

#pragma endregion