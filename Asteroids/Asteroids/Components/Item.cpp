#include "Item.h"


Item::Item(void)
{
	this->setType(ITEM);
}


Item::~Item(void)
{
}

sf::Packet Item::getPacket() {
	sf::Packet packet;
	return packet;
}