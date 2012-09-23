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

void Unit::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Unit::refresh(sf::Packet packet) {
}