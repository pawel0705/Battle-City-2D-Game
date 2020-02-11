#include "Explosion.h"

#pragma region Constructors

Explosion::Explosion(const sf::Vector2f & position, GameReference m_ptr)
	:explosion_position(position),
	m_ptr(m_ptr)
{}

Explosion::Explosion(const sf::Vector2f & position, GameReference m_ptr, bool tank_explode)
	:explosion_position(position),
	m_ptr(m_ptr), tank_explode(tank_explode)
{}

Explosion::~Explosion()
{}

#pragma endregion

#pragma region  Class methods

void Explosion::Updating(double deltaTime) //update explosion
{
	if (tank_explode == false) //normal explosion (projectile, wall)
	{

		if (clock.getElapsedTime().asSeconds() > 0.5f / explode_frames.size())
		{
			if (iterator_frames < explode_frames.size() - 1)
			{
				iterator_frames++;
			}
			else
			{
				explosion_sprite.setTexture(explode_frames.at(iterator_frames));
				isDeleted = true;
			}
			explosion_sprite.setTexture(explode_frames.at(iterator_frames));

			clock.restart();
		}
		explosion_sprite.setPosition(explosion_position.x + 32, explosion_position.y + 32);

	}
	else //tank exploding
	{
		if (clock.getElapsedTime().asSeconds() > 0.1f)
		{
			iterator_frames++;
			clock.restart();
		}
		
		if (iterator_frames < 5)
		{
			explosion_sprite.setTextureRect(sf::IntRect(iterator_frames * 64, 0, 64, 64));
		}
		else if (iterator_frames < 9)
		{
			explosion_sprite.setTextureRect(sf::IntRect((iterator_frames-5) * 64, 64, 64, 64));
		}
		else if (iterator_frames < 14)
		{
			explosion_sprite.setTextureRect(sf::IntRect((iterator_frames-9) * 64, 64 * 2, 64, 64));
		}
		else if (iterator_frames < 19)
		{
			explosion_sprite.setTextureRect(sf::IntRect((iterator_frames-14) * 64, 64 * 3, 64, 64));
		}
		else if (iterator_frames < 23)
		{
			explosion_sprite.setTextureRect(sf::IntRect((iterator_frames-19) * 64, 64 * 4, 64, 64));
		}
		
		if(iterator_frames >= 23)
		{
			isDeleted = true;
		}
	}
}

void Explosion::Input()
{
	//nothing here
}

void Explosion::Drawing(double DeltaTime)
{
	m_ptr->m_window.draw(explosion_sprite); //draw explosions
}

void Explosion::Initialization()
{ 
	iterator_frames = 0;
	if (tank_explode == false)
	{
		for (int i = 1; i <= 6; i++)
		{
			//get textures from file
			m_ptr->textureManager.LoadAsset("explosion_" + std::to_string(i), "textures/explosion_" + std::to_string(i) +".png");
			explode_frames.push_back(m_ptr->textureManager.GetAsset("explosion_" + std::to_string(i)));
		}

		explosion_sprite.setTexture(explode_frames.at(iterator_frames));

		sf::Vector2f origin = sf::Vector2f(explosion_sprite.getGlobalBounds().width / 2, explosion_sprite.getGlobalBounds().height / 2);
		explosion_sprite.setOrigin(origin);
	}
	else
	{
		m_ptr->textureManager.LoadAsset("tank_explosion.png", "textures/tank_explosion.png");
		explosion_sprite.setTexture(m_ptr->textureManager.GetAsset("tank_explosion.png"));
		explosion_sprite.setPosition(explosion_position.x, explosion_position.y);
	}
}

#pragma endregion

#pragma region Accessors

bool Explosion::GetIsDeleted() const
{
	return this->isDeleted; //return state if explosion is deleted
}

#pragma endregion