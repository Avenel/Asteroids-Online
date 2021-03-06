#include "Display.h"


Display::Display(void)
{
	this->setType(DISPLAY);
}


Display::~Display(void)
{
}

void Display::setDisplayObject(View* view) {
	this->displayObject = view;
}

View* Display::getDisplayObject() {
	return this->displayObject;
}

void Display::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Display::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
}

void Display::draw(sf::RenderWindow *target, sf::RenderStates &states) {
	this->displayObject->draw(target, states);
}

void Display::setPosition(float x, float y) {
	this->displayObject->setPosition(x, y);
}

void Display::setRotation(float degree) {
	this->displayObject->setRotation(degree);
}