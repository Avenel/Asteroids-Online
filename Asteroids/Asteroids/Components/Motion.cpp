#include "Motion.h"


Motion::Motion(void)
{
	this->setType(MOTION);
	this->speedX = 0;
	this->speedY = 0;
	this->damping = 0;
}


Motion::~Motion(void)
{
}

sf::Packet* Motion::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void Motion::refresh(sf::Packet packet) {
}

void Motion::increaseSpeed(int rotation, float accelerationRate) {
	this->speedX = (float)(cos(rotation * M_PI / 180)) * accelerationRate;
	this->speedY = (float)(sin(rotation * M_PI / 180)) * accelerationRate;

	this->speedX *= 0.55;
	this->speedY *= 0.55;
}

float Motion::getSpeedX() {
	return this->speedX;
}

float Motion::getSpeedY() {
	return this->speedY;
}