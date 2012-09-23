#include "Bullet.h"


Bullet::Bullet(void)
{
	this->setType(BULLET);
	this->rangeRemaining = 0;
}


Bullet::~Bullet(void)
{
}

void Bullet::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Bullet::refresh(sf::Packet packet) {
}

void Bullet::setRangeRemaining(float rangeRemaining) {
	this->rangeRemaining = rangeRemaining;
}

float Bullet::getRangeRemaining() {
	return this->rangeRemaining;
}
