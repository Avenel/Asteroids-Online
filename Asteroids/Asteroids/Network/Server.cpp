#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port, EntityManager *manager) {	
	this->port = port;

	this->socket.setBlocking(true);
	this->socket.bind(port);

	this->entityManager = manager;
	this->entityMap = manager->getAllEntitiesMap();
	this->entitiesFlat = manager->getAllEntitiesFlat();
	
	this->updateTime = 5;

	this->lastObjectId = -1;
	this->clientList = new list<sf::IpAddress>();

	this->listenThread = new sf::Thread(&Server::listen, this);
	this->synchronizeThread = new sf::Thread(&Server::synchronizeClients, this);
	this->id = sf::IpAddress().getLocalAddress().toInteger();
	this->clientId = sf::IpAddress().getLocalAddress().toInteger();
	this->master = false;
}


Server::~Server(void) {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
	this->socket.unbind();

	delete this->listenThread;
	delete this->synchronizeThread;
	delete this->clientList;
}


void Server::start() {
	this->registerObject(this);
	this->registerClient(sf::IpAddress::LocalHost);

	this->listenThread->launch();

	if (this->master) this->synchronizeThread->launch();
}

void Server::stop() {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
}

void Server::listen() {
	sf::IpAddress address;

	int id;
	int clientId;
	int type;
	Entity* temp;
	unsigned short tempPort;

	while(true) {
		sf::Packet packet;
		tempPort = this->port;
		this->socket.receive(packet, address, tempPort);

		bool ipFound = false;
		if (packet >> id >> clientId >> type) {
			//cout << "RECEIVED DATA: " << address.toString() << endl;
			// Ip-Adresse bekannt?
			for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				if ( it->toInteger() == address.toInteger()) {
					ipFound = true;
					break;
				}
			}

			if (!ipFound && id == -1) {
				// Client registrieren
				packet << address.toString();
				this->refresh(packet);
				continue;
			}
		
			// Id auspacken und weiterleiten, falls Entity schon bekannt
			bool idFound = false;
			
			temp = this->entityManager->getEntity(id, clientId, type);
			if (temp != 0) {
				temp->refresh(packet);
			} else {
				// Entity noch nicht bekannt -> anlegen	
				if (id > -1) {
					this->registerObject(this->generateEntity(id, clientId, type, packet));
				}
			}
		}
	}
}

void Server::registerObject(Entity *object) {
	//cout << "Registered unknown Object: "<< object->getId() << ", " << object->getClientId() << endl;
	this->entityManager->addEntity(object);
	this->lastObjectId++;
}

void Server::registerClient(sf::IpAddress address) {
	this->clientList->push_back(address);
	cout << "Registered Client: " << address.toString() << endl;
}

void Server::deRegisterObject(Entity *object) {
	this->entityManager->deleteEntity(object);
}

void Server::deRegisterClient(sf::IpAddress address) {
	for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		if ( it->toInteger() == address.toInteger()) this->clientList->erase(it);
	}
}

void Server::refresh(sf::Packet packet) {
	string address;
	if (packet >> address) {
		this->registerClient(sf::IpAddress(address));
	}
}

Entity* Server::generateEntity(int id, int clientId, int type, sf::Packet packet) {	
	Entity *temp = new Entity(0,0);
	temp->setClientId(clientId);
	temp->setId(id);

	switch(type) {
	// Default Typ
	case 0:
		int x, y;
		packet >> x >> y;
		temp->setX(x);
		temp->setY(y);

		break;
	// Schiff, Asteroid, etc...
	case 1:
		break;
	default:
		break;
	}

	return temp;
}

int Server::generateObjectId() {
	return (this->lastObjectId+1);
}

void Server::sendData(Entity *object) {
	for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		// Keine Pakete an sich selbst versenden.
		if (it->toInteger() == sf::IpAddress::LocalHost.toInteger() || it->toInteger() == sf::IpAddress().getLocalAddress().toInteger()) continue;

		unsigned short temp = this->port;
		if (object->getClientId() == this->id) {
			// Server hat dieses Objekt erstellt
			this->socket.send(object->getPacket(sf::IpAddress().getLocalAddress().toInteger()), (*it), temp);
		} else {
			// Objekt kommt von einem Clienten, verändere nicht die clientId
			this->socket.send(object->getPacket(0), (*it), temp);
		}
	}
}

void Server::synchronizeClients() {
	// Update Clients every xx ms
	cout << "Synchronize Thread startet" << endl;
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
				sendData((*it));
			}
			time = clock.restart();
		}
	}
}

bool Server::isMaster() {
	return this->master;
}

void Server::setMaster(bool master) {
	this->master = master;
}


std::list<Entity*>* Server::getObjectList() {
	return this->entitiesFlat;
}