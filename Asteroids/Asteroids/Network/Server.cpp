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
	this->updateRequestTime = 100;

	this->clientList = new list<sf::IpAddress>();

	this->listenThread = new sf::Thread(&Server::listen, this);
	this->synchronizeThread = new sf::Thread(&Server::synchronizeClients, this);
	this->handleRequestsThread = new sf::Thread(&Server::handleRequests, this);

	this->id = sf::IpAddress().getLocalAddress().toInteger();
	this->clientId = sf::IpAddress().getLocalAddress().toInteger();
	this->master = false;
	this->seqNr = 0;

	this->incomingRequests = new std::list<Request>();
	this->outgoingRequests = new std::list<Request>();
	this->affirmedRequests = new std::list<Request>();
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
	delete this->affirmedRequests;
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
		controlTag: = -4 => AffirmedRequest senden
					= -3 => Answer auf Request
					= -2 => DeRegister Client
					= -1 => Register Client
					=  0 => Create Entity
					=  1 => Refresh Entity
		
		request:	=  0 => Keine Antwort
				    =  1 => Antworten

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
		if (packet >> seqNr >> clientId >> request >> controlTag) {
			cout << "RECEIVED DATA: " << address.toString() << ": " << seqNr << ", "<< clientId << ", " << request << ", controlTag: " << controlTag << endl;

			// Ip-Adresse bekannt?
			for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				if ( it->toInteger() == address.toInteger()) {
					ipFound = true;
					break;
				}
			}

			if (!ipFound && controlTag == -1) {
				// Client registrieren
				registerClient(address);
				packet >> data;
			} else if(controlTag == -2) {
				// Client deregistrieren
				deRegisterClient(address);
				packet >> data;
			}
			
			// Incoming/Outgoing Requests
			if (request) {

				// INCOMING REQUESTS
				// Nachsehen ob es sich um einen vorhandenen Request handelt, der auf eine Antwort vom Clienten gewartet hat
				// ->IncomingRequests 

				bool incomingRequestFound = false;
				for (std::list<Request>::iterator it = this->incomingRequests->begin(); it != this->incomingRequests->end(); ++it) {
					if ((*it).getClientId() == clientId && (*it).getSeqNr() == seqNr) {
						incomingRequestFound = true;
						packet >> data;
						
						// Wenn ctrlTag = -4 => AffirmedRequest Antwort erhalten => IncomingRequest löschen, da abgearbeitet
						if (controlTag == -4) {
							this->incomingRequests->erase(it);
						}
						break;
					}
				}

				// OUTGOING REQUESTS
				bool outgoingRequestFound = false;
				for (std::list<Request>::iterator it = this->outgoingRequests->begin(); it != this->outgoingRequests->end(); ++it) {
					if ((*it).getClientId() == clientId && (*it).getSeqNr() == seqNr) {
						outgoingRequestFound = true;
						packet >> data;
						this->outgoingRequests->erase(it);							
					}
					break;
				}

				// Basic-Antwort Paket. Vll könnte man hier später mal über Server Dienste reden (ScoreList, mapchangeRequest, ...)
				// IncomingRequest aufnehmen
				if (!incomingRequestFound && !outgoingRequestFound) {
					sf::Packet answerPacket;
					//				SeqNr,	ClientId, request, ctrlTag, Data
					answerPacket << seqNr << clientId << true << -3 << 0;
					Request newRequest(address, seqNr, clientId, answerPacket);
					this->incomingRequests->push_back(newRequest);
					cout << "New Incoming Request from: " << sf::IpAddress(clientId).toString() << endl;
				}

				// Wenn ctrlTag = -3 => Antwort auf Request erhalten => OutgoingRequest löschen, da abgearbeitet, AffirmedRequest senden
				if (controlTag == -3) {
					sf::Packet answerPacket;
					answerPacket << seqNr << clientId << true << -4 << 0;
					Request	newRequest(address, seqNr, clientId, answerPacket);
					this->affirmedRequests->push_back(newRequest);
				}

				// Anmeldungen und Abmeldungen werden alleine, ohne weitere Daten, versand.
				// Answers und AffirmedRequests ebenso
				if (controlTag == -1 || controlTag == -2 || controlTag == -3 || controlTag == -4) continue;
			}

			while(!packet.endOfPacket()) {
				packet >> controlTag >> id >> clientId;
				// Id auspacken und weiterleiten, falls Entity schon bekannt			
				temp = this->entityManager->getEntity(id, clientId);

				//cout << "ControlTag ist: " << controlTag << endl;
				if (temp != 0) {
					switch(controlTag) {
					case 1:
						// aktualisiere Entity inkl. Components
						temp->refresh(&packet);
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
						this->registerObject(this->generateEntity(id, clientId, &packet));
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

Entity* Server::generateEntity(int id, int clientId, sf::Packet *packet) {	
	Entity *temp = this->entityCreator->createStarship();
	temp->setClientId(clientId);
	temp->setId(id);
	
	cout << "Generate Entity!" << endl;

	// CREATE ENTITY mit dem EntityCreator
	
	packet->clear();
	return temp;
}

void Server::sendData(sf::Packet packet, int seqNr) {
	for (list<sf::IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		// Keine Pakete an sich selbst versenden.
		if (it->toInteger() == sf::IpAddress::LocalHost.toInteger() || it->toInteger() == sf::IpAddress().getLocalAddress().toInteger()) continue;

		Request	newRequest((*it), seqNr, this->id, packet);
		this->outgoingRequests->push_back(newRequest);

		unsigned short temp = this->port;
		this->socket.send(packet, (*it), temp);
	}
}

void Server::synchronizeClients() {
	// Update Clients every xx ms
	cout << "Synchronize Thread startet" << endl;
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			// Paket erstellen
			sf::Packet packet;

			// Header
			int seqNr = this->getNextSeq(); 
			packet << seqNr << this->id << true;

			// Paket mit Daten aus den Entities befüllen
			for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
				(*it)->addDataToPacket(&packet);
			}

			//Paket an Clients senden
			sendData(packet, seqNr);

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
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateRequestTime) {		

			// INCOMING REQUESTS (Antworten auf diese, ctrlTag = -3)
			if (!this->incomingRequests->empty()) {
				Request answer = this->incomingRequests->front();
				this->socket.send(answer.getPacket(), answer.getAddress(), this->port);
				this->incomingRequests->push_back(answer);
				this->incomingRequests->pop_front();
				// cout << "IncomingRequestCount: " << this->incomingRequests->size() << endl;
			}

			// AFFIRMED REQUESTS (Antworten auf diese, ctrlTag = -4)
			if (!this->affirmedRequests->empty()) {
				Request affirmRequest = this->affirmedRequests->front();
				this->socket.send(affirmRequest.getPacket(), affirmRequest.getAddress(), this->port);
				this->affirmedRequests->pop_front();
				// cout << "AffirmedRequestCount: " << this->affirmedRequests->size() << endl;
			}

			// OUTGOING REQUESTS (Eigene Anfragen versenden)
			if (!this->outgoingRequests->empty()) {
				Request outgoingRequest = this->outgoingRequests->front();

				this->socket.send(outgoingRequest.getPacket(), outgoingRequest.getAddress(), this->port);
				this->outgoingRequests->push_back(outgoingRequest);
				this->outgoingRequests->pop_front();
				// cout << "OutgoingRequestCount: " << this->outgoingRequests->size() << endl;
			}

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

std::list<Request>* Server::getOutgoingRequests() {
	return this->outgoingRequests;
}

int Server::getNextSeq() {
	return this->seqNr++;
}