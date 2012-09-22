#include "Gun.h"


Gun::Gun(void)
{
	this->setType(GUN);
	this->bulletRange = 0;
}


Gun::~Gun(void)
{
}

sf::Packet Gun::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Gun::refresh(sf::Packet packet) {
}

void Gun::setBulletRange(float bulletRange) {
	this->bulletRange = bulletRange;
}

float Gun::getBulletRange() {
	return this->bulletRange;
}

void Gun::setBulletSpeed(float bulletSpeed) {
	this->bulletSpeed = bulletSpeed;
}

float Gun::getBulletSpeed() {
	return this->bulletSpeed;
}