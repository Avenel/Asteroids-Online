#include "Bullet.h"


Bullet::Bullet(void)
{
	this->setType(BULLET);
	this->rangeRemaining = 0;
}


Bullet::~Bullet(void)
{
}

sf::Packet Bullet::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Bullet::refresh(sf::Packet packet) {
}

void Bullet::setRangeRemaining(float rangeRemaining) {
	this->rangeRemaining = rangeRemaining;
}

float Bullet::getRangeRemaining() {
	return this->rangeRemaining;
}
