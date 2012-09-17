#include <SFML/Graphics.hpp>
#include "Network\Server.h"
#include "Network\Client.h"
#include "Entity\Entity.h"
#include "Systems\SystemManager.h"
#include "Systems\MotionControlSystem.h"
#include <iostream>

using namespace std;
using namespace sf;

int mainMB()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Asteroids Online!");
    
	// SystemManager
	SystemManager systemManager;

	// EntityManager
	EntityManager entityManager;

	// MotionControlSystem
	MotionControlSystem motionCtrlSystem;

	// Systeme hinzufügen
	systemManager.addSystem(&entityManager);
	systemManager.addSystem(&motionCtrlSystem);

	// Test-Server
	Server server(1337, &entityManager);
	server.setMaster(true);
	server.start();

	// Test Client und Registrierung
	Client client(IpAddress("192.168.2.101"), 1337);
	if (server.isMaster()) {
		client.setServerAddress(IpAddress("127.0.0.1"));
	} else {
		client.registerToServer();
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

		systemManager.updateSystems();

		window.clear();
		window.display();
    }

	system("PAUSE");
    return 0;
}