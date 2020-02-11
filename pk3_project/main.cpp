#include "Game.h"
#include <iostream>

#include <stdlib.h> 
#include <crtdbg.h>  

int main(int argc, char *argv[]) try
{
	Game game; //create game
	game.RunGame(); //run game
	return EXIT_SUCCESS;
}
catch (...) //error occurated
{
	std::cerr << "Fatal Error!\nPress enter to exit appication. " << std::endl;
	return EXIT_FAILURE;
}