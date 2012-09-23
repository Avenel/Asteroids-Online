#include "GameState.h"


GameState::GameState(void) {
}


GameState::~GameState(void) {
}

void GameState::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void GameState::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
}