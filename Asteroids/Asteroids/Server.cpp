#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port) {	
	this->port = port;

	this->socket.setBlocking(false);
	this->socket.bind(port);

	this->updateTime = 1000;

	this->lastObjectId = -1;
	this->objectList = new vector<GameObject*>();
	this->clientList = new vector<IpAddress>();

	this->listenThread = new Thread(&Server::listen, this);
	this->synchronizeThread = new Thread(&Server::synchronizeClients, this);
	this->id = -1;
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
		int type;

		Packet packet;
		unsigned short temp = this->port;
		this->socket.receive(packet, address, temp);

		bool ipFound = false;
		if (packet >> id >> type) {
			// Ip-Adresse bekannt?
			for (vector<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				if ( it->toInteger() == address.toInteger()) {
					ipFound = true;
					break;
				}
			}

			if (!ipFound) {
				cout << id << endl;
				if (id == -1) {
					// Client registrieren
					this->refresh(packet);
				}
				continue;
			}
		
			// Id auspacken und weiterleiten, falls GameObject schon bekannt
			cout << id << ", " << type << endl;
			bool idFound = false;
			for (vector<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it)	{ 
				if ( (*it)->getId() == id) {
					(*it)->refresh(packet);
					idFound = true;
					break;
				}
			}
		
			// GameObject noch nicht bekannt -> anlegen	
			if (!idFound) {
				this->registerObject(this->generateGameObject(type, packet));
			}
		}
	}
}

void Server::registerObject(GameObject *object) {
	cout << "Registered unknown Object: "<< object->getId() << endl;
	this->objectList->push_back(object);
	this->lastObjectId++;
}

void Server::registerClient(IpAddress address) {
	this->clientList->push_back(address);
	cout << "Registered Client: " << address.toString() << endl;
}

void Server::deRegisterObject(GameObject *object) {
	for (vector<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
		if ( (*it)->getId() == id) this->objectList->erase(it);
	}
}

void Server::deRegisterClient(IpAddress address) {
	for (vector<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
		if ( it->toInteger() == address.toInteger()) this->clientList->erase(it);
	}
}

void Server::refresh(Packet packet) {
	string address;
	if (packet >> address) {
		this->registerClient(IpAddress(address));
	}
}

GameObject* Server::generateGameObject(int type, Packet packet) {
	cout << "Generate Object: " << type << endl;
	
	int id = this->generateObjectId();
	GameObject *temp = new GameObject(id);

	switch(type) {
	// Default Typ
	case 0:
		int x, y;
		packet >> x >> y;
		temp->setX(x);
		temp->setY(y);

		cout << "Create Type 0: " << x << ", " << y << endl;

		return temp;
		break;
	// Schiff, Asteroid, etc...
	case 1:
		break;
	default:
		return new GameObject(id);
	}
}

int Server::generateObjectId() {
	return (this->lastObjectId+1);
}

void Server::sendDataTo() {
	IpAddress address = this->localThreadAddress;
	for (vector<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
		unsigned short temp = this->port;
		this->socket.send((*it)->getPacket(), address, temp);
	}
}

void Server::synchronizeClients() {
	// Update Clients every xx ms
	cout << "Synchronize Thread startet" << endl;
	Clock clock;
	Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			// Starte für jeden Clienten einen eigenen Thread
			for (vector<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				// Noch etwas "experimentell"...
				// Keine Pakete an sich selbst versenden.
				if (it->toInteger() == IpAddress::LocalHost.toInteger() || it->toInteger() == IpAddress().getLocalAddress().toInteger()) continue;

				this->localThreadAddress = (*it);
				Thread sendDataThread(&Server::sendDataTo, this);
				sendDataThread.launch();
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


std::vector<GameObject*>* Server::getObjectList() {
	return this->objectList;
}