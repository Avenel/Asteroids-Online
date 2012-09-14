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

	while(true) {
		Packet packet;
		this->socket.receive(packet, address, this->port);
		
		std::string message;
		if (packet >> message) {
			// Show the address of the sender
			cout << address << std::endl;
			// Show the message
			cout << message << std::endl; 
		}
	}
}