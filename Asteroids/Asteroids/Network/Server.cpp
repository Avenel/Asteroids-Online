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

	this->updateTime = 10;

	this->clientList = new list<sf::IpAddress>();

	this->listenThread = new sf::Thread(&Server::listen, this);
	this->synchronizeThread = new sf::Thread(&Server::synchronizeClients, this);
	this->handleRequestsThread = new sf::Thread();

	this->id = sf::IpAddress().getLocalAddress().toInteger();
	this->clientId = sf::IpAddress().getLocalAddress().toInteger();
	this->master = false;
	this->seqNr = 0;

	this->incomingRequests = new std::list<Request>();
	this->outgoingRequests = new std::list<Request>();
}


Server::~Server(void) {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
	this->socket.unbind();

	delete this->listenThread;
	delete this->synchronizeThread;
	delete this->clientList;
	delete this->incomingRequests;
	delete this->outgoingRequests;
}


void Server::start() {
	this->registerClient(sf::IpAddress::LocalHost);
	this->listenThread->launch();
	this->handleRequestsThread->launch();

	if (this->master) this->synchronizeThread->launch();
}

void Server::stop() {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
	this->handleRequestsThread->terminate();
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
	int seqNr;
	bool request;
	int data;
	unsigned short tempPort;
	Entity* temp;

	while(true) {
		sf::Packet packet;
		tempPort = this->port;
		this->socket.receive(packet, address, tempPort);

		bool ipFound = false;
		if (packet >> seqNr >> clientId >> request) {
			//cout << "RECEIVED DATA: " << address.toString() << ": " << clientId << ", " << id << endl;
			// Ip-Adresse bekannt?
			for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				if ( it->toInteger() == address.toInteger()) {
					ipFound = true;
					break;
				}
			}

			packet >> controlTag;
			if (!ipFound && controlTag == -1) {
				// Client registrieren
				registerClient(address);
				packet >> data;
				continue;
			} else if(controlTag == -2) {
				// Client deregistrieren
				deRegisterClient(address);
				packet >> data;
				continue;
			}
			
			// Wenn Paket eine Antwort erwartet, lege sie in die entsprechende Queue ab
			if (request) {
				// Nachsehen ob es sich um einen vorhandenen Request handelt, der auf eine Antwort vom Clienten gewartet hat
				bool requestFound = false;
				for (std::list<Request>::iterator it = this->incomingRequests->begin(); it != this->incomingRequests->end(); ++it) {
					if ((*it).getClientId() == clientId && (*it).getSeqNr() == seqNr) {
						requestFound = true;
						packet >> data;
						this->incomingRequests->remove((*it));
					}
				}

				// Basic-Antwort Paket. Vll könnte man hier später mal über Server Dienste reden (ScoreList, mapchangeRequest, ...)
				sf::Packet answerPacket;
				answerPacket << seqNr << clientId << 0;
				Request newRequest(seqNr, clientId, answerPacket);
				this->incomingRequests->push_back(newRequest);
			}

			while(!packet.endOfPacket()) {
				packet >> controlTag >> id;
				// Id auspacken und weiterleiten, falls Entity schon bekannt			
				temp = this->entityManager->getEntity(id, clientId);

				//cout << "ControlTag ist: " << controlTag << endl;
				if (temp != 0) {
					switch(controlTag) {
					case 1:
						// aktualisiere Entity inkl. Components
						temp->refresh(packet);
						break;
					case 2:
						// lösche Entity
						this->deRegisterObject(temp);
						break;
					default:
						break;
					}				
				} else {
					// Entity noch nicht bekannt -> anlegen	
					//cout << "Lege neues Objekt an" << endl;
					if (controlTag == 0) {
						this->registerObject(this->generateEntity(id, clientId, packet));
					}
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
			/*std::list<sf::Packet*> *packets = object->getPackets(sf::IpAddress().getLocalAddress().toInteger());
			for (std::list<sf::Packet*>::iterator packet = packets->begin(); packet != packets->end(); ++packet) {
				this->socket.send((*(*packet)), (*it), temp);
				delete (*packet);
			}
			delete packets;*/
		} else {
			// Objekt kommt von einem Clienten, verändere nicht die clientId
			std::list<sf::Packet> packets = object->getPackets(0);
			for (std::list<sf::Packet>::iterator packet = packets.begin(); packet != packets.end(); ++packet) {
				/*int clientId, id, type;
				(*(*packet)) >> clientId >> id >> type;
				cout << "Schicke: " << clientId << ", " << id << ", " << type << endl;
				(*(*packet)) << clientId << id << type;*/
				this->socket.send((*packet), (*it), temp);
			}
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
			time = clock.getElapsedTime();
		}
	}
}

// Beantworte alle x ms die Anfragen eines clienten
void Server::handleRequests() {
	cout << "HandleRequest Thread startet" << endl;
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			Request answer = this->incomingRequests->front();
			this->socket.send(answer.getPacket(), sf::IpAddress(answer.getClientId()), this->port);
			this->incomingRequests->push_back(answer);
			this->incomingRequests->pop_front();
			time = clock.getElapsedTime();
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