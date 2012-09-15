#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port) {	
	this->port = port;

	this->socket.setBlocking(false);
	this->socket.bind(port);

	this->updateTime = 10;

	this->lastObjectId = -1;
	this->objectList = new vector<GameObject*>();
	this->clientList = new vector<IpAddress>();

	this->listenThread = new Thread(&Server::listen, this);
	this->synchronizeThread = new Thread(&Server::synchronizeClients, this);
	this->id = -1;
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
	this->synchronizeThread->launch();
}

void Server::stop() {
	this->listenThread->terminate();
	this->synchronizeThread->terminate();
}

void Server::listen() {
	IpAddress address;
	int id;

	while(true) {
		Packet packet;
		unsigned short temp = this->port;
		this->socket.receive(packet, address, temp);

		// Ip-Adresse bekannt?
		bool ipFound = false;
		for (vector<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
			if ( it->toInteger() == address.toInteger()) {
				ipFound = true;
				break;
			}
		}

		if (!ipFound) continue;

		// Id auspacken und weiterleiten, falls GameObject schon bekannt
		if (packet >> id) {
			for (vector<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it)
			{ 
				if ( (*it)->getId() == id) (*it)->refresh(packet);
			}
		} else {
			// GameObject noch nicht bekannt -> anlegen
			int type;
			if (packet >> type) {
				this->registerObject(this->generateGameObject(type, packet));
			}
		}
	}
}

void Server::registerObject(GameObject *object) {
	this->objectList->push_back(object);
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
	String address;
	if (packet >> address) {
		this->registerClient(IpAddress(address));
	}
}

GameObject* Server::generateGameObject(int type, Packet packet) {
	int id = this->generateObjectId();

	switch(type) {
	// Default Typ
	case 0:
		&GameObject(id);
		break;
	// Schiff, Asteroid, etc...
	case 1:
		break;
	default:
		return &GameObject(id);
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
	Clock clock;
	Time time = clock.getElapsedTime();
	while(true) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+this->updateTime) {
			// Starte für jeden Clienten einen eigenen Thread
			for (vector<IpAddress>::iterator it = this->clientList->begin(); it != this->clientList->end(); ++it) {
				// Noch etwas "experimentell"...
				this->localThreadAddress = (*it);
				Thread sendDataThread(&Server::sendDataTo, this);
				sendDataThread.launch();
			}
			time = clock.restart();
		}
	}
}

