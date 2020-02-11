#include "MapFile.h"
#include <iostream>

#pragma region Constructors

MapFile::MapFile() {}

MapFile::MapFile(std::string filename)
{
	this->filename = filename; //get map name
}

MapFile::~MapFile()
{
	for (int i = 0; i < sizeX; i++) //delete dynamic 2D array
		delete[] map[i];

	delete[] map;
}

#pragma endregion

#pragma region Class methods

void MapFile::LoadMap() //load map from file
{
	if (filename[filename.size() - 3] == 't' && filename[filename.size() - 2] == 'x' && filename[filename.size() - 1] == 't') //if "txt" at the end of name
	{
		std::ifstream openfile("maps/" + filename); //read as txt
		if (openfile.is_open())
		{
			openfile >> sizeX >> sizeY;

			map = new int *[sizeX];
			for (int i = 0; i < sizeX; i++)
			{
				map[i] = new int[sizeY];
			}

			while (!openfile.eof())
			{
				openfile >> map[counterX][counterY];
				counterX++;
				if (counterX >= sizeX)
				{
					counterX = 0;
					counterY++;
				}
			}
			openfile.close();
		}
		else
		{
			std::cerr << "FAILED LOADING MAP" << std::endl;
		}
	}
	else //read as binary (created by player)
	{
		sizeX = 19;
		sizeY = 11;

		map = new int *[sizeX];
		for (int i = 0; i < sizeX; i++)
		{
			map[i] = new int[sizeY];
		}

		std::ifstream inBinFile;
		inBinFile.open("maps/" + filename, std::ios::in | std::ios::binary);
		if (inBinFile.is_open())
		{

			for (int row = 0; row < sizeX; row++) {

				for (int column = 0; column < sizeY; column++)
				{
					inBinFile.read(reinterpret_cast<char *>(&map[row][column]), sizeof(int));
				}
			}
		}
		else
		{
			std::cerr << "FAILED LOADING MAP" << std::endl;
		}
		inBinFile.close();
	}
}

#pragma endregion