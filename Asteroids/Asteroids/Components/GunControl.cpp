#include "GunControl.h"


GunControl::GunControl(void)
{
	this->setType(GUNCONTROL);
}


GunControl::~GunControl(void)
{
}

void GunControl::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}
void GunControl::refresh(sf::Packet packet) {
}

void GunControl::setShootKey(sf::Keyboard::Key key) {
	this->shootKey = key;
}

sf::Keyboard::Key GunControl::getShootKey() {
	return this->shootKey;
}