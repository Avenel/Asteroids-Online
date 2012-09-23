#include "Item.h"


Item::Item(void)
{
	this->setType(ITEM);
}


Item::~Item(void)
{
}

void Item::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Item::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
}