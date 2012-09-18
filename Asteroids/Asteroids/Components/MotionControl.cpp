#include "MotionControl.h"


MotionControl::MotionControl(void)
{
	this->setType(MOTIONCONTROL);
}


MotionControl::~MotionControl(void)
{
}

sf::Packet MotionControl::getPacket() {
	sf::Packet packet;
	return packet;
}

void MotionControl::refresh(sf::Packet packet) {
}