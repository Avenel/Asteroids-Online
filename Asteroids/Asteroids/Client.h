#pragma once

#include <SFML/Network.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Client
{
public:
	Client(void);

	Client(IpAddress address, unsigned short port);

	~Client(void);

	void send();

private: 
	IpAddress serverAddress;
	UdpSocket socket;
	unsigned short port;
};

