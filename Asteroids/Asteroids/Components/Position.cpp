#include "Position.h"


Position::Position(float x, float y, int rotation)
{
	this->setType(POSITION);
	this->x = x;
	this->y = y;
	this->rotation = rotation;
}


Position::~Position(void)
{
}

void Position::setX(float x) {
	this->x = x;
}

void Position::setY(float y) {
	this->y = y;
}

float Position::getX() {
	return x;
}

float Position::getY() {
	return y;
}

void Position::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << this->x << this->y << this->rotation;
}

void Position::refresh(sf::Packet packet) {
	packet >> this->x >> this->y >> this->rotation;
}

void Position::rotateLeft(float speed) {
	this->rotation -= speed;
}

void Position::rotateRight(float speed) {
	this->rotation += speed;
}

int Position::getRotation() {
	return ((this->rotation));
}