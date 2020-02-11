#include "Projectile.h"

#pragma region Constructors

Projectile::Projectile(GameReference ptr) : m_ptr(ptr)
{
	m_ptr->textureManager.LoadAsset("projectile", "textures/projectile.png"); //get textures from file
	projectile_sprite.setTexture(m_ptr->textureManager.GetAsset("projectile"));

	projectile_rectangle.setSize(sf::Vector2f(32, 32));
	projectile_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

Projectile::~Projectile() {}

#pragma endregion

#pragma region Class methods


void Projectile::Drawing(double deltaTime)
{
	this->m_ptr->m_window.draw(projectile_sprite); //draw projectile
}

void Projectile::Updating(double deltaTime)
{
	double movement = projectile_speed * deltaTime; //set the appropriate speed adjusted to the user's equipment

	switch (projectile_direction) //depending on the direction, set the appropriate sprite
	{
	case 1:
		projectile_sprite.setTextureRect(sf::IntRect(0, 32 * 1, 32, 32));
		projectile_rectangle.move(0, -movement);
		break;
	case 2:
		projectile_sprite.setTextureRect(sf::IntRect(0, 32 * 3, 32, 32));
		projectile_rectangle.move(0, movement);
		break;
	case 3:
		projectile_sprite.setTextureRect(sf::IntRect(0, 32 * 2, 32, 32));
		projectile_rectangle.move(-movement, 0);
		break;
	case 4:
		projectile_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		projectile_rectangle.move(movement, 0);
		break;
	default:
		break;
	}

	counter_life++;
	if (counter_life > proj_lifetime) //check life expectancy, if it is exceeded, set the information about the removal
	{
		SetDestroyed(true);
		counter_life = 0;
	}
	projectile_sprite.setPosition(projectile_rectangle.getPosition());
}

#pragma endregion

#pragma region operators

Projectile & Projectile::operator*=(const int & x)
{
	this->projectile_speed *= x; //set the appropriate projectile speed
	return *this;
}

#pragma endregion

#pragma region accesors

void Projectile::SetDirection(int projectile_direction)
{
	this->projectile_direction = projectile_direction; //set the direction of the projectile
}

void Projectile::SetRectanglePosition(float x, float y)
{
	this->projectile_rectangle.setPosition(x, y); //set the initial x and y of the projectile
}

void Projectile::SetProjectileStatus(int projectile_status)
{
	this->projectile_status = projectile_status; //set the status of the projectile
}

void Projectile::SetDestroyed(bool destroyed)
{
	this->destroyed = destroyed; //set information about the destruction of the projectile
}

int Projectile::GetProjectileStatus() const
{
	return this->projectile_status; //return the status of the projectile
}

bool Projectile::GetDestroyed() const
{
	return this->destroyed; //return information about the destruction of the projectile
}

sf::RectangleShape Projectile::GetRectangle() const
{
	return this->projectile_rectangle; //return rectangle
}

#pragma endregion