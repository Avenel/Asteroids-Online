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
	/**
		Funktioniert wie folgt:
		controlTag: >= 0 => Wird als Unit-Enum verstanden
					= -1 => Entity wird neu angelegt
					= -2 => Entity wird entfernt
		Wenn controlTag = -1, dann werden der nachfolgende Int Entity-Type verstanden und der EntityCreator dementsprechend benutzt.
	*/
	int controlTag;
	unsigned short tempPort;
	Entity* temp;

	while(true) {
		sf::Packet packet;
		tempPort = this->port;
		this->socket.receive(packet, address, tempPort);

		bool ipFound = false;
		if (packet >> clientId >> id) {
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
			temp = this->entityManager->getEntity(id, clientId);

			sf::Packet tempPacket = packet;
			tempPacket >> controlTag;
			if (temp != 0) {
				if (controlTag == -2) {
					this->deRegisterObject(temp);
				} else {
					temp->refresh(packet);
				}
			} else {
				// Entity noch nicht bekannt -> anlegen	
				if (controlTag == -1) {
					this->registerObject(this->generateEntity(id, clientId, tempPacket));
				}
			}
		}
	}
}

void Server::registerObject(Entity *object) {
	//cout << "Registered unknown Object: "<< object->getId() << ", " << object->getClientId() << endl;
	this->entityManager->addEntity(object);
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

Entity* Server::generateEntity(int id, int clientId, sf::Packet packet) {	
	Entity *temp = new Entity(0);
	temp->setClientId(clientId);
	temp->setId(id);
	
	// CREATE ENTITY mit dem EntityCreator

	return temp;
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