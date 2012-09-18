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

sf::Packet Display::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Display::refresh(sf::Packet packet) {
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