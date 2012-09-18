#include "MotionControl.h"


MotionControl::MotionControl(void)
{
	this->setType(MOTIONCONTROL);
}


MotionControl::~MotionControl(void)
{
}

sf::Packet* MotionControl::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void MotionControl::refresh(sf::Packet packet) {
}