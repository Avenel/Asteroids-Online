#pragma once

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>

#include "..\Entity\GameObject.h"
#include <iostream>
#include <list>
#include <Rpc.h>

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
	void sendData(GameObject *object);

	void registerClient(IpAddress address);
	void registerObject(GameObject *object);

	void deRegisterClient(IpAddress address);
	void deRegisterObject(GameObject *object);

	int generateObjectId();

	void refresh(Packet packet);

	bool isMaster();
	void setMaster(bool master);

	std::list<GameObject*>* getObjectList();
	
protected:
	bool master;

	int serverId;

	unsigned int port;
	UdpSocket socket;
	
	// Später soll es mehrere Threads geben -> Skalierbarkeit
	Thread *listenThread;
	Thread *synchronizeThread;

	int lastObjectId;
	std::list<GameObject*> *objectList;
	std::list<IpAddress> *clientList;

	float updateTime;
	IpAddress localThreadAddress;

	GameObject* generateGameObject(int id, int clientId, int type, Packet packet);
};

