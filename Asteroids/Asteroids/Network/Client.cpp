#include "Client.h"


Client::Client(void) {}

Client::Client(sf::IpAddress address, unsigned short port) {
	this->serverAddress = address;
	this->port = port;

	this->socket.bind(port);
	this->socket.setBlocking(false);
	
	this->clientId = sf::IpAddress().getPublicAddress().toInteger();
	this->objectList = new list<Entity*>();
}


Client::~Client(void) {
	delete this->objectList;
}

void Client::send() {
	for (list<Entity*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
		std::list<sf::Packet> packets = (*it)->getPackets(this->clientId);
		for (std::list<sf::Packet>::iterator it = packets.begin(); it != packets.end(); ++it) {
			socket.send((*it), this->serverAddress, this->port);			
		}
	}
}

void Client::registerObject(Entity *object) {
	this->objectList->push_back(object);
}

void Client::registerToServer() {
	sf::Packet packet;
	packet << this->clientId << -1 << 0;

	socket.send(packet, this->serverAddress, this->port);
}

void Client::setServerAddress(sf::IpAddress address) {
	this->serverAddress = address;
}