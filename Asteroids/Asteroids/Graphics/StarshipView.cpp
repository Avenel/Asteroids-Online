#include "StarshipView.h"

//Groesse des Starship
float const ::StarshipView::size( 16.0 ); 

StarshipView::StarshipView(void)
{
	//Dreieckiges Starship definieren
	this->shipPolygon = new sf::ConvexShape();
	this->shipPolygon->setPointCount(3);
	this->shipPolygon->setPoint(0, sf::Vector2f(0,0));
	this->shipPolygon->setPoint(1, sf::Vector2f(0,this->size));
	this->shipPolygon->setPoint(2, sf::Vector2f(this->size,this->size/2.0f));

	//Farbe und Aussehen
	//this->shipPolygon->setFillColor(sf::Color::Black);
	//this->shipPolygon->setOutlineColor(sf::Color::White);
	//this->shipPolygon->setOutlineThickness(1.0f);
	
	//Schwerpunkt bei einem gleichschenkligen Dreieck
	this->shipPolygon->setOrigin(this->size/3.0f, this->size/2.0f);
}


StarshipView::~StarshipView(void){
	delete this->shipPolygon;
}

void StarshipView::draw(sf::RenderWindow *target, sf::RenderStates &states) {
	target->draw((*this->shipPolygon));
}


void StarshipView::setPosition(float x, float y) {
	this->shipPolygon->setPosition(x, y);
}

void StarshipView::setRotation(float degree) {
	this->shipPolygon->setRotation(degree);
}

