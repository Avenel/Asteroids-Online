#include "Client.h"


Client::Client(void) {}

Client::Client(sf::IpAddress address, unsigned short port, std::list<Request>* outgoingRequests) {
	this->serverAddress = address;
	this->port = port;

	this->seqNr = 0;

	this->socket.bind(port);
	this->socket.setBlocking(false);
	
	this->clientId = sf::IpAddress().getLocalAddress().toInteger();
	this->objectList = new list<Entity*>();

	// Anfragen an den Server benötigen eine Liste, die vom Server verwaltet wird
	this->outgoingRequests = outgoingRequests;
}


Client::~Client(void) {
	delete this->objectList;
}

void Client::send() {
	for (list<Entity*>::iterator it = this->objectList->begin(); it != this->objectList->end(); ++it) {
		std::list<sf::Packet> packets = (*it)->getPackets(this->clientId);
		for (std::list<sf::Packet>::iterator it = packets.begin(); it != packets.end(); ++it) {
			//socket.send((*it), this->serverAddress, this->port);			
		}
	}
}

void Client::registerObject(Entity *object) {
	this->objectList->push_back(object);
}

void Client::registerToServer() {
	sf::Packet packet;
	int seqNr = 12345;//this->getNextSeq();
	packet << seqNr << this->clientId << true << -1 << 0;

	Request	newRequest(this->serverAddress, seqNr, clientId, packet);
	this->outgoingRequests->push_back(newRequest);

	//this->socket.send(packet, this->serverAddress, this->port);
}

void Client::setServerAddress(sf::IpAddress address) {
	this->serverAddress = address;
}

int Client::getNextSeq() {
	return this->seqNr++;
}
	