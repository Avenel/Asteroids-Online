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
	
	for (vector<GameObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); ++it)
	{
		Packet packet = (*it)->getPacket();
		socket.send(packet, this->serverAddress, this->port);		
	}

}

void Client::registerObject(GameObject *object)
{
	this->objectList.push_back(object);
}

void Client::registerToServer()
{
	Packet packet;
	packet << -1;

	socket.send(packet, this->serverAddress, this->port);		
}