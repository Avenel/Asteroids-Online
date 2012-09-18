#include "Asteroid.h"


Asteroid::Asteroid(void) {
	this->setType(ASTEROID);
}


Asteroid::~Asteroid(void) {
}

sf::Packet Asteroid::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Asteroid::refresh(sf::Packet packet) {
}