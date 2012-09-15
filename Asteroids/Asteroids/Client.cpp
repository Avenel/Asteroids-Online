#include "Client.h"


Client::Client(void) {}

Client::Client(IpAddress address, unsigned short port) {
	this->serverAddress = address;
	this->port = port;

	this->socket.bind(port);
	this->socket.setBlocking(false);
	
	this->clientId = IpAddress().getPublicAddress().toInteger();
}


Client::~Client(void) {}

void Client::send() {
	for (vector<GameObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); ++it) {
		Packet packet = (*it)->getPacket(this->clientId);
		socket.send(packet, this->serverAddress, this->port);		
	}
}

void Client::registerObject(GameObject *object) {
	this->objectList.push_back(object);
}

void Client::registerToServer() {
	Packet packet;
	packet << -1 << 0 << 0 << IpAddress().getLocalAddress().toString();

	socket.send(packet, this->serverAddress, this->port);
}

void Client::setServerAddress(IpAddress address) {
	this->serverAddress = address;
}