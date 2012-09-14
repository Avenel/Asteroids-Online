#include <SFML/Graphics.hpp>

#include "Server.h"

using namespace std;
using namespace sf;


int main()
{	
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	int x = 10;
	sf::CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(x, 10);

	Server server(4567);
	server.start();

	while(true) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			x--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
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