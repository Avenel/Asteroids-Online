#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Client.h"
#include "GameObject.h"
#include <iostream>

using namespace std;
using namespace sf;

int main()
{

	cout << IpAddress().getPublicAddress().toInteger() << endl;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    
	CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(50, 20);

	CircleShape shape2(10.f);
	shape2.setFillColor(Color::Red);
	shape2.setPosition(50, 50);

	// Test GameObjects
	vector<CircleShape> shapes;
	shapes.push_back(shape);
	shapes.push_back(shape2);

	GameObject ball(0, 0);
	ball.setX(10);
	ball.setY(50);

	GameObject ball2(1, 0);
	ball2.setX(150);
	ball2.setY(150);

	// Test-Server
	Server server(1337);
	server.setMaster(true);
	server.start();

	// Test Client und Registrierung
	Client client(IpAddress("192.168.2.101"), 1337);

	if (server.isMaster()) {
		client.setServerAddress(IpAddress("127.0.0.1"));
		client.registerToServer();
		client.registerObject(&ball);

		server.registerObject(&ball);
	} else {
		client.registerToServer();
		client.registerObject(&ball2);

		server.registerObject(&ball2);
		server.registerClient(IpAddress("192.168.2.101"));
	}

	bool active = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				window.close();
				server.stop();
				return 0;
			}

			if (event.type == Event::GainedFocus) active = true;
			if (event.type == Event::LostFocus) active = false;
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && active) {
			server.stop();
			window.close();
			return 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && active) {
			if (server.isMaster()) {
				ball.setX(10);
			} else {
				ball2.setX(10);
				client.send();
				cout << "Left" << endl;
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && active) {
			if (server.isMaster()) {
				ball.setX(150);
			} else {
				ball2.setX(150);
				client.send();
				cout << "Right" << endl;
			}
			
		}


		// TEMP Zeichne Kreise
		window.clear();
		int i = -1;
		for (vector<GameObject*>::iterator it = server.getObjectList()->begin(); it != server.getObjectList()->end(); ++it)	{ 
			if (i>=0 && i < 2) {
				shapes[i].setPosition((*it)->getX(), (*it)->getY());
				window.draw(shapes[i]);
			}
			i++;
		}
       
		window.display();
    }

	system("PAUSE");
    return 0;
}