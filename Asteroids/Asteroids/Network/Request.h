#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Request
{
public:
	Request(void);
	Request(sf::IpAddress address, int seqNr, int clientId, sf::Packet packet);
	
	~Request(void);

	int getSeqNr();
	int getClientId();
	sf::Packet getPacket();
	sf::IpAddress getAddress();

private:
	sf::Packet packet;
	sf::IpAddress address;
	int clientId;
	int seqNr;
};

