#include "Gun.h"


Gun::Gun(void)
{
	this->setType(GUN);
}


Gun::~Gun(void)
{
}

sf::Packet Gun::getPacket() {
	sf::Packet packet;
	return packet;
}

void Gun::refresh(sf::Packet packet) {
}