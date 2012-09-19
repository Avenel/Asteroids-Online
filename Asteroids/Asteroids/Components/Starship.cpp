#include "Starship.h"


Starship::Starship()
{
	this->setType(STARSHIP);
}


Starship::~Starship(void)
{
}

sf::Packet Starship::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Starship::refresh(sf::Packet packet) {
}