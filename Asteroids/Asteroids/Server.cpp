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
			// Show the address of the sender
			cout << address << std::endl;
			// Show the message
			cout << "Message has arrived!" << std::endl; 

			packet << id << x << y;

			for (vector<GameObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); ++it)
			{
				if ( (*it)->getId() == id) (*it)->refresh(packet);
				cout << "Object "<< id << " refreshed!" << std::endl; 
				cout << "X "<< x << " refreshed!" << std::endl; 
				cout << "Y "<< y << " refreshed!" << std::endl; 
			}

		}
	}
}

void Server::registerObject(GameObject *object)
{
	this->objectList.push_back(object);
}