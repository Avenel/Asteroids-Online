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

sf::Packet Motion::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Motion::refresh(sf::Packet packet) {
}

void Motion::increaseSpeed(int rotation, float accelerationRate) {
	this->speedX += (float)(cos(rotation * M_PI / 180)) * accelerationRate;
	this->speedY += (float)(sin(rotation * M_PI / 180)) * accelerationRate;
	this->getSpeedRotation();
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

float Motion::getSpeedRotation() {
	float speedRotation = 0.0f;
	if(this->speedX != 0.0f) {
		speedRotation = atan (this->speedY/this->speedX) * 180 / M_PI;
	}
	else if (this->speedY >= 0.0f) {
		speedRotation = 90.0f;
	}
	else {
		speedRotation = 270.f;
	}

	if(this->speedX >= 0.0f && this->speedY < 0.0f) {
		speedRotation += 360.0f;
	}
	else if(this->speedX < 0.0f) {
		speedRotation += 180.0f;	
	}
	
	return speedRotation;
}