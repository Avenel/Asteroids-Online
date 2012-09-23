#include "Asteroid.h"


Asteroid::Asteroid(void) {
	this->setType(ASTEROID);
}


Asteroid::~Asteroid(void) {
}

void Asteroid::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Asteroid::refresh(sf::Packet packet) {
}