#include "Entity.h"


Entity::Entity(void) {
	this->id = 0;
	this->units = new map<Unit::UnitType, Unit*>();
	this->synchronized = false;
}

Entity::Entity(int id) {
	this->id = id;
	this->units = new map<Unit::UnitType, Unit*>();
	this->synchronized = false;
}

Entity::~Entity(void){
	delete this->units;
}

void Entity::refresh(sf::Packet packet){
	int componentType;
	packet >> componentType;

	if (!this->hasComponent(Unit::UnitType(componentType))) return;

	(*this->units)[Unit::UnitType(componentType)]->refresh(packet);
}

int Entity::getId() { 
	return this->id;
}

void Entity::setId(int id) {
	this->id = id;
}

std::list<sf::Packet> Entity::getPackets(int clientId) {
	std::list<sf::Packet> packets;
	if (clientId != 0) this->clientId = clientId;
	
	sf::Packet packet;
	// Wenn Entity noch nicht synchronisiert wurde, setze ControlTag auf -1
	if (!this->synchronized) {
		packet << this->clientId << this->id << -1;
		this->synchronized = true;
		packets.push_back(packet);
	}

	// Füge alle Packets aus den Komponenten dazu
	// Später kann man noch durch ein isUpdated? unnötige Pakte vermeiden.
	for (std::map<Unit::UnitType, Unit*>::iterator it = this->units->begin(); it != this->units->end(); ++it) {
		sf::Packet packet = (*it).second->getPacket(this->clientId, this->id);
		packets.push_back(packet);
	}

	return packets;
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