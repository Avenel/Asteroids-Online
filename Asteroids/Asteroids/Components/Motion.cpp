#include "Motion.h"


Motion::Motion(void)
{
	this->setType(MOTION);
}


Motion::~Motion(void)
{
}

sf::Packet* Motion::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void Motion::refresh(sf::Packet packet) {
}