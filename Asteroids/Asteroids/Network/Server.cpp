#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port, EntityManager *manager, EntityCreator *creator) {	
	this->port = port;

	this->socket.setBlocking(true);
	this->socket.bind(port);

	this->entityManager = manager;
	this->entityMap = manager->getAllEntitiesMap();
	this->entitiesFlat = manager->getAllEntitiesFlat();
	
	this->entityCreator = creator;

	this->updateTime = 0;

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
			//cout << "RECEIVED DATA: " << address.toString() << ": " << clientId << ", " << id << endl;
			// Ip-Adresse bekannt?
			for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				if ( it->toInteger() == address.toInteger()) {
					ipFound = true;
					break;
				}
			}

			if (!ipFound && id == -1) {
				// Client registrieren
				registerClient(address);
				continue;
			}
		
			// Id auspacken und weiterleiten, falls Entity schon bekannt			
			temp = this->entityManager->getEntity(id, clientId);

			sf::Packet tempPacket = packet;
			tempPacket >> controlTag;
			//cout << "ControlTag ist: " << controlTag << endl;
			if (temp != 0 && controlTag != -1) {
				if (controlTag == -2) {
					//cout << "Loesche Entity" << endl;
					this->deRegisterObject(temp);
				} else {
					//cout << "Aktualisiere Komponente" << endl;
					temp->refresh(packet);
				}
			} else {
				// Entity noch nicht bekannt -> anlegen	
				//cout << "Lege neues Objekt an" << endl;
				if (controlTag == -1) {
					this->registerObject(this->generateEntity(id, clientId, tempPacket));
				}
			}
		}
	}
}

void Server::registerObject(Entity *object) {
	cout << "Registered unknown Object: "<< object->getId() << ", " << object->getClientId() << endl;
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
	std::string address;
	if (packet >> address) {
		//cout << "Gelesene Adresse: " << address << endl;
		this->registerClient(sf::IpAddress(address));
	}
}

Entity* Server::generateEntity(int id, int clientId, sf::Packet packet) {	
	Entity *temp = this->entityCreator->createStarship();
	temp->setClientId(clientId);
	temp->setId(id);
	
	cout << "Generate Entity!" << endl;

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
			std::list<sf::Packet*> *packets = object->getPackets(sf::IpAddress().getLocalAddress().toInteger());
			for (std::list<sf::Packet*>::iterator packet = packets->begin(); packet != packets->end(); ++packet) {
				this->socket.send((*(*packet)), (*it), temp);
				delete (*packet);
			}
			delete packets;
		} else {
			// Objekt kommt von einem Clienten, verändere nicht die clientId
			std::list<sf::Packet*> *packets = object->getPackets(0);
			for (std::list<sf::Packet*>::iterator packet = packets->begin(); packet != packets->end(); ++packet) {
				/*int clientId, id, type;
				(*(*packet)) >> clientId >> id >> type;
				cout << "Schicke: " << clientId << ", " << id << ", " << type << endl;
				(*(*packet)) << clientId << id << type;*/
				this->socket.send((*(*packet)), (*it), temp);
				delete (*packet);
			}
			delete packets;
		}
	}
}

void Server::synchronizeClients() {
	// Update Clients every xx ms
	cout << "Synchronize Thread startet" << endl;
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	while(true) {
		//if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
				sendData((*it));
			}
			//time = clock.restart();
		//}
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