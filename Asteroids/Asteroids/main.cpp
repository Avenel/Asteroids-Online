#include <SFML/Graphics.hpp>

#include "Server.h"
#include "Client.h"

using namespace std;
using namespace sf;


int main()
{	
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	int x = 10;
	sf::CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(x, 10);

	// Test-Server
	Server server(1337);
	server.start();

	// Test Client
	Client client(IpAddress::LocalHost, 1337);

	while(true) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			client.send();
			x--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			client.send();
			x++;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			server.stop();
			window.close();
			return 0;
		}


		shape.setPosition(x, 10);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;

}