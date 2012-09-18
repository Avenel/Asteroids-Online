#include "Motion.h"


Motion::Motion(void)
{
	this->setType(MOTION);
}


Motion::~Motion(void)
{
}

sf::Packet Motion::getPacket() {
	sf::Packet packet;
	return packet;
}

void Motion::refresh(sf::Packet packet) {
}