#pragma once

#include <SFML/Network.hpp>
#include "GameObject.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Server
{
public:
	Server();
	Server(unsigned short port);

	~Server(void);

	void start();
	void stop();

	void listen();
	
	void registerObject(GameObject *object);


private:
	
	unsigned short port;
	UdpSocket socket;
	Thread *serverThread;

	std::vector<GameObject*> objectList;

};

