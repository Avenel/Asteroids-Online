#pragma once

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>

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
	void synchronizeClients();
	void sendDataTo();

	void registerClient(IpAddress address);
	void registerObject(GameObject *object);

	void deRegisterClient(IpAddress address);
	void deRegisterObject(GameObject *object);

	int generateObjectId();

	virtual void refresh(Packet packet);
	
protected:
	
	unsigned short port;
	UdpSocket socket;
	
	// Später soll es mehrere Threads geben -> Skalierbarkeit
	Thread *listenThread;
	Thread *synchronizeThread;

	int lastObjectId;
	std::vector<GameObject*> *objectList;
	std::vector<IpAddress> *clientList;

	float updateTime;
	IpAddress localThreadAddress;

	GameObject* generateGameObject(int type, Packet packet);
};

