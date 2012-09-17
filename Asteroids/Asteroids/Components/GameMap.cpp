#include "GameMap.h"


GameMap::GameMap(void)
{
	this->setType(GAMEMAP);
}


GameMap::~GameMap(void)
{
}

sf::Packet GameMap::getPacket() {
	sf::Packet packet;
	return packet;
}