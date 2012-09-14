#pragma once

#include <SFML/Network.hpp>
#include "GameObject.h"
#include <iostream>
#include <vector>

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

private: 
	IpAddress serverAddress;
	UdpSocket socket;
	unsigned short port;

	std::vector<GameObject*> objectList;
};

