#include "Asteroid.h"


Asteroid::Asteroid(void) {
	this->setType(ASTEROID);
}


Asteroid::~Asteroid(void) {
}

sf::Packet Asteroid::getPacket() {
	sf::Packet packet;
	return packet;
}