#include "Game.h"


Game::Game(void) {
}


Game::~Game(void) {
}

void Game::startUp() {
	// Bootsrap, Initialisierungskram

	// Window erstellen
	this->window = new sf::RenderWindow(sf::VideoMode(200, 200), "Asteroids Online!");

	// Systeme hinzufügen
	this->systemManager = new SystemManager();
	this->familyManager = new FamilyManager();
	this->entityManager = new EntityManager(this->familyManager);
	this->gameManager = new GameManager();
	this->motionControlSystem = new MotionControlSystem();
	this->renderSystem = new RenderSystem(this->familyManager, this->window);
	addSystems();

	// Netzwerk
	this->server = new Server(1337, this->entityManager);
	server->setMaster(false);
	server->start();

	// EntityCreator
	this->entityCreator = new EntityCreator();

	this->entityManager->addEntity(this->entityCreator->createStarship());

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
	this->systemManager->addSystem(this->familyManager);
	this->systemManager->addSystem(this->entityManager);
	this->systemManager->addSystem(this->gameManager);
	this->systemManager->addSystem(this->renderSystem);
}

void Game::run() {
	// Spielstart, evtl Mainloop    
	bool active = true;

    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				this->window->close();
				server->stop();
				return;
			}

			if (event.type == sf::Event::GainedFocus) active = true;
			if (event.type == sf::Event::LostFocus) active = false;
        }

		this->window->clear();
		this->systemManager->updateSystems();
		this->window->display();
    }

}
