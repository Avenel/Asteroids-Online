#pragma once

#include <SFML/Network.hpp>

class Request
{
public:
	Request(void);
	Request(int seqNr, int clientId, sf::Packet packet);
	
	~Request(void);

	int getSeqNr();
	int getClientId();
	sf::Packet getPacket();

private:
	sf::Packet packet;
	int clientId;
	int seqNr;
};

