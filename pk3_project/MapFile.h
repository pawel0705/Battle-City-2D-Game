#ifndef MapFile_hpp
#define MapFile_hpp

#include <string>
#include <fstream>

class MapFile //the class that reads the map from a file
{
	friend class GameLoop; //friendship with class 'GameLoop'

private:
	int counterX = 0;
	int counterY = 0;
	int sizeX = 0;
	int sizeY = 0;
	int **map;  //dynamic array that stores numbers that represent the block type

	bool is_binary_file = false;

	std::string filename = "missing file";

public:
	MapFile();
	MapFile(std::string filename);
	~MapFile();

	void LoadMap(); //load map from file
};

#endif