#include "Game.h"


Game::Game(void) {
}


Game::~Game(void) {
}

void Game::startUp() {
	// Bootsrap, Initialisierungskram

	// Systeme hinzufügen
	this->systemManager = new SystemManager();
	this->entityManager = new EntityManager();
	this->gameManager = new GameManager();
	this->motionControlSystem = new MotionControlSystem();
	this->renderSystem = new RenderSystem();
	addSystems();

	// Netzwerk
	this->server = new Server(1337, this->entityManager);
	server->setMaster(false);
	server->start();

	this->client = new Client(sf::IpAddress("192.168.2.101"), 1337);
	if (server->isMaster()) {
		client->setServerAddress(sf::IpAddress("127.0.0.1"));
	} else {
		client->registerToServer();
		server->registerClient(sf::IpAddress("192.168.2.101"));
	}
}

void Game::addSystems() {
	this->systemManager->addSystem(this->motionControlSystem);
	this->systemManager->addSystem(this->entityManager);
	this->systemManager->addSystem(this->gameManager);
	this->systemManager->addSystem(this->renderSystem);
}

void Game::run() {
	// Spielstart, evtl Mainloop

	sf::RenderWindow window(sf::VideoMode(200, 200), "Asteroids Online!");
    
	bool active = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				window.close();
				server->stop();
				return;
			}

			if (event.type == sf::Event::GainedFocus) active = true;
			if (event.type == sf::Event::LostFocus) active = false;
        }

		systemManager->updateSystems();

		window.clear();
		window.display();
    }

}
