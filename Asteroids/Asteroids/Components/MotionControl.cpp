#include "MotionControl.h"


MotionControl::MotionControl(void)
{
	this->setType(MOTIONCONTROL);
}


MotionControl::~MotionControl(void)
{
}

sf::Packet MotionControl::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void MotionControl::refresh(sf::Packet packet) {
}

void MotionControl::setLeft(sf::Keyboard::Key key) {
	this->left = key;
}

sf::Keyboard::Key MotionControl::getLeft() {
	return this->left;
}

void MotionControl::setRight(sf::Keyboard::Key key) {
	this->right = key;
}

sf::Keyboard::Key MotionControl::getRight() {
	return this->right;
}

void MotionControl::setAccelerate(sf::Keyboard::Key key) {
	this->accelerate = key;
}

sf::Keyboard::Key MotionControl::getAccelerate() {
	return this->accelerate;
}

void MotionControl::setAccelerationRate(float accelerationRate) {
	this->accelerationRate = accelerationRate;
}

float MotionControl::getAccelerationRate() {
	return this->accelerationRate;
}

void MotionControl::setRotationRate(float rotationRate) {
	this->rotationRate = rotationRate;
}

float MotionControl::getRotationRate() {
	return this->rotationRate;
}