#pragma once

#include <SFML/Network.hpp>
#include "GameObject.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Server : GameObject
{
public:
	Server();
	Server(unsigned short port);

	~Server(void);

	void start();
	void stop();

	void listen();
	
	void registerClient(IpAddress address);
	void registerObject(GameObject *object);

	void deRegisterClient(IpAddress address);
	void deRegisterObject(GameObject *object);

	int createObjectId();

	virtual void refresh(Packet packet);

private:
	
	unsigned short port;
	UdpSocket socket;
	Thread *serverThread;

	std::vector<GameObject*> *objectList;
	std::vector<IpAddress> *clientList;

};

