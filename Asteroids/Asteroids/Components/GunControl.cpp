#include "GunControl.h"


GunControl::GunControl(void)
{
	this->setType(GUNCONTROL);
}


GunControl::~GunControl(void)
{
}

sf::Packet* GunControl::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void GunControl::refresh(sf::Packet packet) {
}