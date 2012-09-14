#include "Server.h"


Server::Server(void)
{
}

Server::Server(unsigned short port)
{	
	this->port = port;

	this->address = IpAddress::LocalHost;
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
	while(true) {
		Packet packet;
		this->socket.receive(packet, this->address, this->port);
		
		char x[128];
		if (packet >> x) {
			// Show the address of the sender
			cout << address << std::endl;
			// Show the message
			cout << x << std::endl; 
		}
	}
}