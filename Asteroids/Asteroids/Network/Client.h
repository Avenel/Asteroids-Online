#pragma once

#include <SFML/Network.hpp>
#include "..\Entity\Entity.h"
#include <iostream>
#include <list>

using namespace std;

class Client
{
public:
	Client(void);

	Client(sf::IpAddress address, unsigned short port);

	~Client(void);

	void send();

	void registerObject(Entity *object);
	void registerToServer();

	void setServerAddress(sf::IpAddress address);

private: 
	sf::IpAddress serverAddress;
	sf::UdpSocket socket;
	unsigned short port;
	int clientId;

	std::list<Entity*> *objectList;
};

