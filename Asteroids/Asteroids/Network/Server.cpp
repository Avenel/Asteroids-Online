#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port) {	
	this->port = port;

	this->socket.setBlocking(true);
	this->socket.bind(port);

	this->updateTime = 5;

	this->lastObjectId = -1;
	this->objectList = new list<GameObject*>();
	this->clientList = new list<IpAddress>();

	this->listenThread = new Thread(&Server::listen, this);
	this->synchronizeThread = new Thread(&Server::synchronizeClients, this);
	this->id = IpAddress().getLocalAddress().toInteger();
	this->clientId = IpAddress().getLocalAddress().toInteger();
	this->master = false;
}


Server::~Server(void) {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
	this->socket.unbind();

	delete this->listenThread;
	delete this->synchronizeThread;
	delete this->clientList;
	delete this->objectList;
}


void Server::start() {
	this->registerObject(this);
	this->registerClient(IpAddress::LocalHost);

	this->listenThread->launch();

	if (this->master) this->synchronizeThread->launch();
}

void Server::stop() {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
}

void Server::listen() {
	IpAddress address;

	while(true) {
		int id;
		int clientId;
		int type;

		Packet packet;
		unsigned short temp = this->port;
		this->socket.receive(packet, address, temp);

		bool ipFound = false;
		if (packet >> id >> clientId >> type) {
			//cout << "RECEIVED DATA: " << address.toString() << endl;
			// Ip-Adresse bekannt?
			for (list<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
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
		
			// Id auspacken und weiterleiten, falls GameObject schon bekannt
			bool idFound = false;
			for (list<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it)	{ 
				if ( ((*it)->getId() == id) && ((*it)->getClientId() == clientId)) {
					(*it)->refresh(packet);
					idFound = true;
					break;
				}
			}
		
			// GameObject noch nicht bekannt -> anlegen	
			if (!idFound && id > -1) {
				this->registerObject(this->generateGameObject(id, clientId, type, packet));
			}
		}
	}
}

void Server::registerObject(GameObject *object) {
	//cout << "Registered unknown Object: "<< object->getId() << ", " << object->getClientId() << endl;
	this->objectList->push_back(object);
	this->lastObjectId++;
}

void Server::registerClient(IpAddress address) {
	this->clientList->push_back(address);
	cout << "Registered Client: " << address.toString() << endl;
}

void Server::deRegisterObject(GameObject *object) {
	for (list<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
		if ( (*it)->getId() == id) this->objectList->erase(it);
	}
}

void Server::deRegisterClient(IpAddress address) {
	for (list<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		if ( it->toInteger() == address.toInteger()) this->clientList->erase(it);
	}
}

void Server::refresh(Packet packet) {
	string address;
	if (packet >> address) {
		this->registerClient(IpAddress(address));
	}
}

GameObject* Server::generateGameObject(int id, int clientId, int type, Packet packet) {	
	GameObject *temp = new GameObject(0,0);
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

void Server::sendData(GameObject *object) {
	for (list<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		// Keine Pakete an sich selbst versenden.
		if (it->toInteger() == IpAddress::LocalHost.toInteger() || it->toInteger() == IpAddress().getLocalAddress().toInteger()) continue;

		unsigned short temp = this->port;
		if (object->getClientId() == this->id) {
			// Server hat dieses Objekt erstellt
			this->socket.send(object->getPacket(IpAddress().getLocalAddress().toInteger()), (*it), temp);
		} else {
			// Objekt kommt von einem Clienten, verändere nicht die clientId
			this->socket.send(object->getPacket(0), (*it), temp);
		}
	}
}

void Server::synchronizeClients() {
	// Update Clients every xx ms
	cout << "Synchronize Thread startet" << endl;
	Clock clock;
	Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			for (list<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
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


std::list<GameObject*>* Server::getObjectList() {
	return this->objectList;
}