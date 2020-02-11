#ifndef Explosion_hpp
#define Explosion_hpp

#include <SFML/Graphics.hpp>

#include "ProgramState.h"
#include "GameAssets.h"

#include <vector>

class Explosion : public ProgramState //the class responsible for the explosions
{
	std::vector<sf::Texture> explode_frames; //Container storing explosions

	GameReference m_ptr; //pointer on the state of the game (state machine)

	unsigned int iterator_frames = 0; //frames of explosion animation

	bool isDeleted = false; //is this the end of the explosion animation
	bool tank_explode = false; //Is this a tank explosion

	sf::Sprite explosion_sprite;
	sf::Vector2f explosion_position;
	sf::Clock clock;

public:
	Explosion(const sf::Vector2f& position, GameReference m_ptr); //constructor for ordinary explosions
	Explosion(const sf::Vector2f& position, GameReference m_ptr, bool tank_explode); //constructor for the explosion of tanks
	~Explosion();

	void Updating(double deltaTime) override; //updating explosions
	void Input() override; //input
	void Drawing(double DeltaTime) override; //draw explosions
	void Initialization() override; //load data

	bool GetIsDeleted() const; //accessor
};

#endif