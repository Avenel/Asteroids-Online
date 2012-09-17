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

sf::Packet Unit::getPacket() {
	sf::Packet packet;
	return packet;
}