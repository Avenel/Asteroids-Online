#include "Item.h"


Item::Item(void)
{
	this->setType(ITEM);
}


Item::~Item(void)
{
}

sf::Packet* Item::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void Item::refresh(sf::Packet packet) {
}