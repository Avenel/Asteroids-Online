#include "Entity.h"


Entity::Entity(void) {
	this->id = 0;
	this->type = EntityType::OBJECT;
	this->units = new list<Unit*>();
}

Entity::Entity(int id, EntityType type) {
	this->id = id;
	this->type = type;
	this->units = new list<Unit*>();
}

Entity::~Entity(void){
	delete this->units;
}

void Entity::refresh(sf::Packet packet){
}

int Entity::getId() { 
	return this->id;
}

void Entity::setId(int id) {
	this->id = id;
}

void Entity::setType(EntityType type) {
	this->type = type;
}

int Entity::getType() {
	return this->type;
}

sf::Packet Entity::getPacket(int clientId) {
	if (clientId != 0) this->clientId = clientId;
	sf::Packet packet;
	packet << this->id << this->clientId << this->type;
	return packet;
}

int Entity::getClientId() {
	return this->clientId;
}

void Entity::setClientId(int clientId) {
	this->clientId = clientId;
}

void Entity::addUnit(Unit *unit) {
	this->units->push_back(unit);
}

void Entity::deleteUnit(Unit *unit) {
	this->units->remove(unit);
}

list<Unit*>* Entity::getAllUnits() {
	return this->units;
}