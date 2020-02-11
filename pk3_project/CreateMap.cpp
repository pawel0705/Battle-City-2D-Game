#include "CreateMap.h"

#pragma region Constructors
CreateMap::CreateMap() : CreateMap(nullptr){}

CreateMap::CreateMap(GameReference m_ptr) : m_ptr(m_ptr) {}

#pragma endregion

#pragma region  Class methods

void CreateMap::Updating(double deltaTime)
{
	sf::Time elapsed = key_clock.getElapsedTime();
	if (decision == false) //put a block on the ground
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (Iter_wall = square.begin(), iterator_1 = 0; Iter_wall != square.end(); Iter_wall++, iterator_1++)
			{
				if (square[iterator_1].GetRectangle().getPosition() == rectangle.getPosition())
				{
					square.erase(Iter_wall);
					break;
				}
			}
			
			key_clock.restart();
			block_counter++;
			decision = true;
			if (block_counter == 1) //creating blocks
			{
				MapCube normal_rock(1, m_ptr);
				normal_rock.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				normal_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 0, 64, 64));
				square.push_back(normal_rock);
			}
			else if (block_counter == 2)
			{
				MapCube harder_rock(2, m_ptr);
				harder_rock.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				harder_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64, 0, 64, 64));
				square.push_back(harder_rock);
			}
			else if (block_counter == 3)
			{
				MapCube water(3, m_ptr);
				water.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				water.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64, 64, 64, 64));
				square.push_back(water);
			}
			else if (block_counter == 4)
			{
				MapCube bush(4, m_ptr);
				bush.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				bush.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 2, 0, 64, 64));
				square.push_back(bush);
			}
			else if (block_counter == 5)
			{
				MapCube bad_rock(5, m_ptr);
				bad_rock.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				bad_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 64, 64, 64));
				square.push_back(bad_rock);
			}
			else if (block_counter == 6)
			{
				MapCube your_base(6, m_ptr);
				your_base.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				your_base.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 2, 64, 64, 64));
				square.push_back(your_base);
			}
			else if (block_counter == 7)
			{
				MapCube spawn_point(7, m_ptr);
				spawn_point.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				spawn_point.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 3, 0, 64, 64));
				square.push_back(spawn_point);
			}
			else if (block_counter == 8)
			{
				MapCube enemy_spawn_point(8, m_ptr);
				enemy_spawn_point.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				enemy_spawn_point.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(64 * 3, 64, 64, 64));
				square.push_back(enemy_spawn_point);

			}
			else if (block_counter == 9)
			{
				MapCube base_rock(9, m_ptr);
				base_rock.SetRectanglePosition(rectangle.getPosition().x, rectangle.getPosition().y);
				base_rock.SetTextureSprite(m_ptr->textureManager.GetAsset("bricks"), sf::IntRect(0, 0, 64, 64));
				square.push_back(base_rock);
			}
			else
			{
				block_counter = 0;
			}
		}
	}

	if (decision == true) //block placed, "if" checks whether it has been approved
	{
		if (elapsed.asSeconds() > 0.2f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				decision = false;
				if (block_counter != 0)
				{
					square.pop_back();
				}
				key_clock.restart();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				decision = false;
				key_clock.restart();

				if (square.back().GetRectangle().getPosition().x > max_x)
				{
					max_x = square.back().GetRectangle().getPosition().x;
				}
				if (square.back().GetRectangle().getPosition().y > max_y)
				{
					max_y = square.back().GetRectangle().getPosition().y;
				}
				
			}
		}
	}
}

void CreateMap::Input()
{
	sf::Event event;

	while (m_ptr->m_window.pollEvent(event)) //checks upcoming events
	{
		if (sf::Event::Closed == event.type) //Close the game window if you click the red cross
		{
			m_ptr->m_window.close();
		}
	}

	sf::Time elapsed_2 = moving_clock.getElapsedTime();

	if (elapsed_2.asSeconds() > 0.1f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //move about 64 pixels
		{
			if (rectangle.getPosition().y != 0)
				rectangle.move(0, -64);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (rectangle.getPosition().y != 11 * 64 - 64)
				rectangle.move(0, 64);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (rectangle.getPosition().x != 0)
				rectangle.move(-64, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (rectangle.getPosition().x != 1280 - 64)
				rectangle.move(64, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			SaveMap();
			m_ptr->m_stateMachine.AddNewState(std::unique_ptr<ProgramState>(new MainMenu(m_ptr))); //go to main menu
		}
		moving_clock.restart();
	}
	sprite.setPosition(rectangle.getPosition());
}

void CreateMap::Drawing(double DeltaTime)
{
	m_ptr->m_window.draw(sprite); //draw a tank

	int iterator_1 = 0;
	for (const auto & iter_square : square) //draw all blocks
	{
		square[iterator_1].Drawing(DeltaTime);
		m_ptr->m_window.draw(square[iterator_1].GetSprite());
		iterator_1++;
	}
}

template<typename T, int height, int width>
std::ostream& CreateMap::writemap(std::ostream& os, T(&map)[height][width]) //write to a file in the appropriate format (especially to a format that will be read correctly in another function)
{
	os << width << ' ' << height << '\n';
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			os << map[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}


void CreateMap::SaveMap() //save map to txt and binary
{
	for (int i = 0; i < max_y / 64; i++) //first fill the map with zeros (to facilitate)
	{
		for (int j = 0; j < max_x / 64; j++)
		{
			created_map[i][j] = 0;
		}
	}

	for (int i = 0; i < max_y / 64; i++) //set the appropriate numbers that indicate the block
	{
		for (int j = 0; j < max_x / 64; j++)
		{
			int iterator_1 = 0;
			for (const auto & iter_cube : square)
			{
				int tmp_x = square[iterator_1].GetRectangle().getPosition().x / 64;
				int tmp_y = square[iterator_1].GetRectangle().getPosition().y / 64;

				created_map[tmp_x][tmp_y] = square[iterator_1].GetTypeOfbrick();
				
				iterator_1++;
			}
		}
	}

	iterator_1 = 0;
	std::ifstream loadfile("maps_file.dat", std::ios_base::binary); //this file contains map names (names of all files with maps)
	if (loadfile.good())
	{
		while (true)
		{
			if (std::getline(loadfile, string_tmp, '\0'))
			{
				iterator_1++;
			}
			if (loadfile.eof())
			{
				break;
			}
		}
	}

	std::fstream file("maps/"+std::to_string(iterator_1)+" Player's map.txt", std::ios::out);

	if (file.is_open())
	{
		writemap(file, created_map);
		writemap(std::cout, created_map);
		file.close();
	}

	std::ofstream outBinFile;
	outBinFile.open("maps/"+std::to_string(iterator_1) + " Player's map.bin", std::ios::out | std::ios::binary); //save map binary
	for (int row = 0; row < 19; row++) 
	{
		for (int column = 0; column < 11; column++) {

			outBinFile.write(reinterpret_cast<char*> (&created_map[row][column]), sizeof(int));
		}
	}
	outBinFile.close();

	std::ofstream savefile("maps_file.dat", std::ios_base::binary | std::ios_base::app); //save map names
	if (savefile.good())
	{
	
		/*
		string_tmp = "DEVELOPER MAP.txt";
		const char *c = string_tmp.c_str();
		savefile.write(c, 17); // write string to binary file
		savefile.write("\0", sizeof(char)); // null end string for easier reading
		*/

		string_tmp = std::to_string(iterator_1) + " Player's map.bin";
		const char *c = string_tmp.c_str();
		savefile.write(c, (std::to_string(iterator_1) + " Player's map.bin").size()); // write string to binary file
		savefile.write("\0", sizeof(char)); // null end string for easier reading
		string_tmp = std::to_string(iterator_1) + " Player's map.txt";
		c = string_tmp.c_str();
		savefile.write(c, (std::to_string(iterator_1) + " Player's map.txt").size());
		savefile.write("\0", sizeof(char));
		savefile.close();
	}
}

void CreateMap::Initialization()
{
	m_ptr->textureManager.LoadAsset("player_tank", "textures/player_tank.png"); //Initialize basic data
	sprite.setTexture(m_ptr->textureManager.GetAsset("player_tank"));
	m_ptr->textureManager.LoadAsset("bricks", "textures/bricks.png");
	sprite.setTextureRect(sf::IntRect(0, 64, 64, 64));
}
#pragma endregion