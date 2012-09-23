#include "Request.h"


Request::Request(void) {
}

Request::Request(sf::IpAddress address, int seqNr, int clientId, sf::Packet packet) {
	this->address = address;
	this->seqNr = seqNr;
	this->clientId = clientId;
	this->packet = packet;
}


Request::~Request(void) {
}

int Request::getClientId() {
	return this->clientId;
}

int Request::getSeqNr() {
	return this->seqNr;
}

sf::Packet Request::getPacket() {
	return this->packet;
}

sf::IpAddress Request::getAddress() {
	return this->address;
}
