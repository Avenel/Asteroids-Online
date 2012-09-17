#include "Starship.h"


Starship::Starship()
{
	this->setType(STARSHIP);
}


Starship::~Starship(void)
{
}

sf::Packet Starship::getPacket() {
	sf::Packet packet;
	return packet;
}