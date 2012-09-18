#include "Entity.h"


Entity::Entity(void) {
	this->id = 0;
	this->units = new map<Unit::UnitType, Unit*>();
}

Entity::Entity(int id) {
	this->id = id;
	this->units = new map<Unit::UnitType, Unit*>();
}

Entity::~Entity(void){
	delete this->units;
}

void Entity::refresh(sf::Packet packet){
	int componentType;
	packet >> componentType;

	(*this->units)[Unit::UnitType(componentType)]->refresh(packet);
}

int Entity::getId() { 
	return this->id;
}

void Entity::setId(int id) {
	this->id = id;
}

sf::Packet Entity::getPacket(int clientId) {
	if (clientId != 0) this->clientId = clientId;
	sf::Packet packet;
	packet << this->clientId << this->id;
	return packet;
}

int Entity::getClientId() {
	return this->clientId;
}

void Entity::setClientId(int clientId) {
	this->clientId = clientId;
}

void Entity::addUnit(Unit *unit) {
	(*units)[unit->getType()] = unit;
}

void Entity::deleteUnit(Unit *unit) {
	this->units->erase(unit->getType());
}

map<Unit::UnitType, Unit*>* Entity::getAllUnits() {
	return this->units;
}

bool Entity::hasComponent(Unit::UnitType type) {
	if((*this->units)[type] != 0) {
		return true;
	}
	return false;
}

Unit* Entity::getComponent(Unit::UnitType type) {
	return (*this->units)[type];
}