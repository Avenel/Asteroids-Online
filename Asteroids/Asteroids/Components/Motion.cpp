#include "Motion.h"


Motion::Motion(void)
{
	this->setType(MOTION);
}


Motion::~Motion(void)
{
}

sf::Packet Motion::getPacket() {
	sf::Packet packet;
	return packet;
}

void Motion::refresh(sf::Packet packet) {
}

void Motion::increaseSpeed(int rotation, int accelerationRate) {
	this->speedX = (cos(rotation * M_PI / 180)) * accelerationRate;
	this->speedY = (sin(rotation * M_PI / 180)) * accelerationRate;
}

float Motion::getSpeedX() {
	return this->speedX;
}

float Motion::getSpeedY() {
	return this->speedY;
}