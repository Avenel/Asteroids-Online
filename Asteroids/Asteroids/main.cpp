#include <SFML/Graphics.hpp>

#include "Server.h"
#include "Client.h"
#include "GameObject.h"

using namespace std;
using namespace sf;


int main()
{	
	RenderWindow window(sf::VideoMode(200, 200), "Asteroids Online!");

	CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(50, 20);

	CircleShape shape2(10.f);
	shape2.setFillColor(Color::Red);
	shape2.setPosition(50, 50);
	
	// Test GameObjects
	GameObject ball(1);
	ball.setX(10);
	ball.setY(50);

	GameObject ball2(2);
	ball2.setX(150);
	ball2.setY(150);

	// Test-Server
	Server server(1337);
	server.start();
	
	// Test Client
	Client client(IpAddress::LocalHost, 1337);

	// Registriere die nötigen Objekte
	client.registerToServer();
	
	server.registerObject(&ball);
	server.registerObject(&ball2);
	
	client.registerObject(&ball);
	client.registerObject(&ball2);
	
	// Sende Testdaten
	client.send();

	while(true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			server.stop();
			window.close();
			return 0;
		}

		shape.setPosition(ball.getX(), ball.getY());
		shape2.setPosition(ball2.getX(), ball2.getY());

		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.display();
	}

	return 0;

}