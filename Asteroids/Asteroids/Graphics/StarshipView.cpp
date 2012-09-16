#include "StarshipView.h"


StarshipView::StarshipView(void)
{
	//Dreieckiges Starship definieren
	this->setPointCount(3);
	this->setPoint(0, sf::Vector2f(0,0));
	this->setPoint(1, sf::Vector2f(0,this->size));
	this->setPoint(2, sf::Vector2f(this->size,this->size/2.0));
}


StarshipView::~StarshipView(void)
{
}
