#include "HPstatus.h"

#pragma region Operators

int HPstatus::operator-(const Enemy & enemy) //change the amount of life depending on the opponent's attack
{
	hp_now -= enemy.GetAD();
	//update the text
	text.setString("HP: " + std::to_string(hp_now) + "/" + std::to_string(hp_max) + "\nLIFE: " + std::to_string(lives-1));;

	if (hp_max-hp_now > hp_max/2)
	{
		text.setFillColor(sf::Color::Red);
	}
	else
	{
		text.setFillColor(sf::Color::Yellow);
	}

	return hp_now;
}

HPstatus & HPstatus::operator++()
{
	this->hp_now = hp_max; //reset the hp indicator
	lives--; //decrement the number of lives

	return *this;
}

HPstatus & HPstatus::operator+(int i)
{
	this->lives += lives + i; //add lives
	return *this;
}

#pragma endregion

#pragma region Accesors

void HPstatus::GetPlayerMaxHP(int player_hp, int lives) //get player's actual HP and lives
{
	this->hp_max = player_hp;
	this->hp_now = player_hp;
	this->lives = lives;
}

#pragma endregion