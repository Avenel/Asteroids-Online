#include "Starship.h"


Starship::Starship(sf::Color color)
{
	this->setPointCount(3);
	this->setPoint(0, sf::Vector2f(0, 0));
	this->setPoint(1, sf::Vector2f(0, 15));
	this->setPoint(2, sf::Vector2f(15, 7.5));
	this->setOutlineColor(color);
	this->setOutlineThickness(1.0);
	this->setFillColor(sf::Color::Black);
}


Starship::~Starship(void)
{
}
