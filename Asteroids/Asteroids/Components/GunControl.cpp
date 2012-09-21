#include "GunControl.h"


GunControl::GunControl(void)
{
	this->setType(GUNCONTROL);
}


GunControl::~GunControl(void)
{
}

sf::Packet GunControl::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void GunControl::refresh(sf::Packet packet) {
}

void GunControl::setShootKey(sf::Keyboard::Key key) {
	this->shootKey = key;
}

sf::Keyboard::Key GunControl::getShootKey() {
	return this->shootKey;
}