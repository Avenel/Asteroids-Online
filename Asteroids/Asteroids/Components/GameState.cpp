#include "GameState.h"


GameState::GameState(void) {
}


GameState::~GameState(void) {
}

sf::Packet GameState::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void GameState::refresh(sf::Packet packet) {
}