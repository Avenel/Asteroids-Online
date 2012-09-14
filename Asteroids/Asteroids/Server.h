#pragma once

#include <SFML/Network.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Server
{
public:
	Server();
	Server(unsigned short port);

	~Server(void);

	void start();
	void stop();

	void listen();

private:
	
	unsigned short port;
	UdpSocket socket;
	Thread *serverThread;

};

