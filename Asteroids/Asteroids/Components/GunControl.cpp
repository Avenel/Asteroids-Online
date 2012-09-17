#include "GunControl.h"


GunControl::GunControl(void)
{
	this->setType(GUNCONTROL);
}


GunControl::~GunControl(void)
{
}

sf::Packet GunControl::getPacket() {
	sf::Packet packet;
	return packet;
}