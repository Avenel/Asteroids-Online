#include "Client.h"


Client::Client(void)
{
}

Client::Client(IpAddress address, unsigned short port)
{
	this->serverAddress = address;
	this->port = port;

	this->socket.bind(port);
	this->socket.setBlocking(false);
}


Client::~Client(void)
{
}

void Client::send()
{
	std::string message = "hello";
	Packet packet;

	packet << message;

	socket.send(packet, this->serverAddress, this->port);
}