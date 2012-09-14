#include <SFML/Graphics.hpp>

#include "Server.h"
#include "Client.h"
#include "GameObject.h"

using namespace std;
using namespace sf;


int main()
{	
	sf::RenderWindow window(sf::VideoMode(200, 200), "Asteroids Online!");

	sf::CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(50, 20);
	
	// Test GameObject
	GameObject ball(1);
	ball.setX(50);
	ball.setY(20);

	// Test-Server
	Server server(1337);
	server.start();

	server.registerObject(&ball);

	// Test Client
	/*Client client(IpAddress::LocalHost, 1337);

	client.send();*/

	while(true) {

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			client.send();
			x--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			client.send();
			x++;
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			server.stop();
			window.close();
			return 0;
		}


		shape.setPosition(ball.getX(), ball.getY());

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;

}