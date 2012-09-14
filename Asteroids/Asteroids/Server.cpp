#include "Server.h"


Server::Server(void)
{
}

Server::Server(unsigned short port)
{	
	this->port = port;

	this->socket.setBlocking(false);
	this->socket.bind(port);

	this->serverThread = new Thread(&Server::listen, this);
}


Server::~Server(void)
{
	this->serverThread->terminate();
	delete this->serverThread;
}


void Server::start()
{
	this->serverThread->launch();
}

void Server::stop() 
{
	this->serverThread->terminate();
}

void Server::listen() {	

	IpAddress address;
	int id, x, y;


	while(true) {
		Packet packet;
		this->socket.receive(packet, address, this->port);
		
		if (packet >> id >> x >> y) {
			packet << id << x << y;

			for (vector<GameObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); ++it)
			{
				if ( (*it)->getId() == id) (*it)->refresh(packet);
			}

		}
	}
}

void Server::registerObject(GameObject *object)
{
	this->objectList.push_back(object);
}