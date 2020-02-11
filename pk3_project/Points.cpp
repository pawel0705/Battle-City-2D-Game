#include "Points.h"

#pragma region operators

Points Points::operator++(int) //increment the number of points
{
	Points more_points = *this;
	score++; //increment
	text.setString("SCORE: " + std::to_string(score)); //set the displayed text with a new number of points
	return std::move(more_points);
}

Points Points::operator+(int points) //add "int" to the number of points
{
	Points more_points = *this;
	score += points; //add more points
	text.setString("SCORE: " + std::to_string(score)); //set a new text showing the number of points
	return std::move(more_points);
}
#pragma endregion