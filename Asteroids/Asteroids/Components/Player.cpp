#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

sf::Packet Player::getPacket(int clientId, int id) {
	sf::Packet packet;
	packet << clientId << id << this->type;
	return packet;
}

void Player::refresh(sf::Packet packet) {
}