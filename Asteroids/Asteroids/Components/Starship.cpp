#include "Starship.h"


Starship::Starship()
{
	this->setType(STARSHIP);
}


Starship::~Starship(void)
{
}

void Starship::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Starship::refresh(sf::Packet packet) {
}