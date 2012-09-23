#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::addDataToPacket(sf::Packet* packet){
	(*packet) << this->type << 0;
}

void Player::refresh(sf::Packet *packet) {
	int data;
	(*packet) >> data; 
}