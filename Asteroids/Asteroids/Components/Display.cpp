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

sf::Packet Display::getPacket() {
	sf::Packet packet;
	return packet;
}

void Display::refresh(sf::Packet packet) {
}