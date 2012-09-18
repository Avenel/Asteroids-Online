#include "GameMap.h"


GameMap::GameMap(void)
{
	this->setType(GAMEMAP);
}


GameMap::~GameMap(void)
{
}

sf::Packet* GameMap::getPacket(int clientId, int id) {
	sf::Packet* packet = new sf::Packet();
	(*packet) << clientId << id << this->type;
	return packet;
}

void GameMap::refresh(sf::Packet packet) {
}