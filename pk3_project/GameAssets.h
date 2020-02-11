#ifndef GameAssets_hpp
#define GameAssets_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AssetManager.h"
#include "StateMachine.h"

struct GameAssets //the structure that stores game assets
{
	AssetManager<sf::Texture> textureManager; //textures
	AssetManager<sf::Font> fontManager; //fonts
	AssetManager<sf::SoundBuffer> soundMenager; //music

	sf::RenderWindow m_window; //window
	StateMachine m_stateMachine; //state machine
};

typedef	std::shared_ptr<GameAssets> GameReference;
#endif