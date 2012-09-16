#include "Entity.h"


Entity::Entity(void) {
	this->id = 0;
	this->type = 0;
	this->x = 0;
	this->y = 0;
}

Entity::Entity(int id, int type) {
	this->id = id;
	this->type = type;
	this->x = 0;
	this->y = 0;
}

Entity::~Entity(void){}

void Entity::refresh(Packet packet){
	packet >> this->x >> this->y;
}

int Entity::getId() { 
	return this->id;
}

int Entity::getX() {
	return this->x;
}

int Entity::getY() {
	return this->y;
}

void Entity::setId(int id) {
	this->id = id;
}

void Entity::setType(int type) {
	this->type = type;
}

int Entity::getType() {
	return this->type;
}

void Entity::setX(int x) {
	this->x = x;
}

void Entity::setY(int y) {
	this->y = y;
}

Packet Entity::getPacket(int clientId) {

	if (clientId != 0) this->clientId = clientId;
	Packet packet;
	packet << this->id << this->clientId << this->type << this->x << this->y;
	return packet;
}

int Entity::getClientId() {
	return this->clientId;
}

void Entity::setClientId(int clientId) {
	this->clientId = clientId;
}