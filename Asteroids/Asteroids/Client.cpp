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
	int id = 1;
	int x = 10;
	int y = 10;
	Packet packet;

	packet << id << x << y;

	socket.send(packet, this->serverAddress, this->port);
}