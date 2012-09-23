#include "GameMap.h"


GameMap::GameMap(void)
{
	this->setType(GAMEMAP);
}


GameMap::~GameMap(void)
{
}

void GameMap::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void GameMap::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
}