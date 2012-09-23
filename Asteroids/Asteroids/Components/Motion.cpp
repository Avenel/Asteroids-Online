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

void Motion::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Motion::refresh(sf::Packet packet) {
}

void Motion::increaseSpeed(float speedX, float speedY) {
	this->speedX += speedX;
	this->speedY += speedY;
}
float Motion::getSpeedX() {
	return this->speedX;
}

float Motion::getSpeedY() {
	return this->speedY;
}
void Motion::setSpeedX(float dx) {
	this->speedX = dx;
}

void Motion::setSpeedY(float dy) {
	this->speedY = dy;
}

float Motion::getDamping() {
	return this->damping;
}

void Motion::setDamping(float damping) {
	this->damping = damping;
}