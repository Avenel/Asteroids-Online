#include "MotionControl.h"


MotionControl::MotionControl(void)
{
	this->setType(MOTIONCONTROL);
}


MotionControl::~MotionControl(void)
{
}

void MotionControl::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void MotionControl::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
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