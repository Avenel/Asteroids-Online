#include "Unit.h"


Unit::Unit(void)
{
}


Unit::~Unit(void)
{
}

void Unit::setType(UnitType type) {
	this->type = type;
}

Unit::UnitType Unit::getType() {
	return this->type;
}

sf::Packet Unit::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Unit::refresh(sf::Packet packet) {
}