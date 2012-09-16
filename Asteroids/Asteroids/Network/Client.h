#pragma once

#include <SFML/Network.hpp>
#include "..\Entity\GameObject.h"
#include <iostream>
#include <list>

using namespace sf;
using namespace std;

class Client
{
public:
	Client(void);

	Client(IpAddress address, unsigned short port);

	~Client(void);

	void send();

	void registerObject(GameObject *object);
	void registerToServer();

	void setServerAddress(IpAddress address);

private: 
	IpAddress serverAddress;
	UdpSocket socket;
	unsigned short port;
	int clientId;

	std::list<GameObject*> *objectList;
};

