#include "Server.h"


Server::Server(void){}

Server::Server(unsigned short port) {	
	::GameObject(-1);
	this->port = port;

	this->socket.setBlocking(false);
	this->socket.bind(port);

	this->lastObjectId = -1;
	this->objectList = new vector<GameObject*>();
	this->clientList = new vector<IpAddress>();

	this->serverThread = new Thread(&Server::listen, this);
}


Server::~Server(void) {
	this->serverThread->terminate();
	delete this->serverThread;
	delete this->clientList;
	delete this->objectList;
}


void Server::start() {
	this->registerObject(this);
	this->registerClient(IpAddress::LocalHost);
	this->serverThread->launch();
}

void Server::stop() {
	this->serverThread->terminate();
}

void Server::listen() {
	IpAddress address;
	int id;

	while(true) {
		Packet packet;
		this->socket.receive(packet, address, this->port);

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