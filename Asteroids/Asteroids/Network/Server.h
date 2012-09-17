#pragma once

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>

#include "..\Entity\Entity.h"
#include "..\Systems\EntityManager.h"
#include <iostream>
#include <list>
#include <Rpc.h>

using namespace std;

class Server : Entity
{
public:
	Server();
	Server(unsigned short port, EntityManager *manager);

	~Server(void);

	void start();
	void stop();

	void listen();
	void synchronizeClients();
	void sendData(Entity *object);

	void registerClient(sf::IpAddress address);
	void registerObject(Entity *object);

	void deRegisterClient(sf::IpAddress address);
	void deRegisterObject(Entity *object);

	void refresh(sf::Packet packet);

	bool isMaster();
	void setMaster(bool master);

	std::list<Entity*>* getObjectList();
	
protected:
	bool master;

	int serverId;

	unsigned int port;
	sf::UdpSocket socket;
	
	// Später soll es mehrere Threads geben -> Skalierbarkeit
	sf::Thread *listenThread;
	sf::Thread *synchronizeThread;

	std::list<sf::IpAddress> *clientList;

	float updateTime;
	sf::IpAddress localThreadAddress;

	EntityManager *entityManager;
	std::map<int, std::map<int, Entity*>*>* entityMap;
	std::list<Entity*>* entitiesFlat;

	Entity* generateEntity(int id, int clientId, sf::Packet packet);
};

