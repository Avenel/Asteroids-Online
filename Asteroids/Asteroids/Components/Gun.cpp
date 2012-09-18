#include "Gun.h"


Gun::Gun(void)
{
	this->setType(GUN);
}


Gun::~Gun(void)
{
}

sf::Packet* Gun::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void Gun::refresh(sf::Packet packet) {
}