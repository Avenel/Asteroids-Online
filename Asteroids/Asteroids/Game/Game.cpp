#include "Game.h"


Game::Game(void) {
	this->windowHeight = 800;
	this->windowWidth = 600;
}

Game::Game(int windowHeight, int windowWidth) {
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
}

Game::~Game(void) {
}

void Game::startUp() {
	// Bootsrap, Initialisierungskram

	// Window erstellen
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowHeight, this->windowWidth), "Asteroids Online!");

	// Systeme hinzufügen
	this->systemManager = new SystemManager();
	this->familyManager = new FamilyManager();
	this->entityManager = new EntityManager(this->familyManager);
	this->gameManager = new GameManager();
	this->motionControlSystem = new MotionControlSystem(this->familyManager);
	this->renderSystem = new RenderSystem(this->familyManager, this->window);
	this->movementSystem = new MovementSystem(this->familyManager, this->window->getSize());
	this->gunControlSystem = new GunControlSystem(this->familyManager, this->entityManager);
	addSystems();

	// Netzwerk
	this->server = new Server(1337, this->entityManager, this->entityCreator);
	server->setMaster(true);
	server->start();

	// Testschiff
	Entity* starship = this->entityManager->createStarship();

	this->client = new Client(sf::IpAddress("192.168.2.104"), 1337, this->server->getOutgoingRequests());
	if (server->isMaster()) {
		client->setServerAddress(sf::IpAddress("127.0.0.1"));
		((Position*)starship->getComponent(Unit::POSITION))->setX(400);
		((Position*)starship->getComponent(Unit::POSITION))->setY(400);
	} else {
		client->registerToServer();
		server->registerClient(sf::IpAddress("127.0.0.1"));
		((Position*)starship->getComponent(Unit::POSITION))->setX(50);
		((Position*)starship->getComponent(Unit::POSITION))->setY(150);
		client->registerObject(starship); 
	}

	//this->client->send();
}

void Game::addSystems() {
	this->systemManager->addSystem(this->gunControlSystem);
	this->systemManager->addSystem(this->motionControlSystem);
	this->systemManager->addSystem(this->gameManager);
	this->systemManager->addSystem(this->renderSystem);
	this->systemManager->addSystem(this->movementSystem);
}

void Game::run() {
	// Spielstart, evtl Mainloop    
	bool active = true;

	cout << sf::IpAddress().getLocalAddress().toString() << endl;

	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();

	sf::Text fps("FPS: ");
	fps.setPosition(this->windowWidth-50, 10);
	
	int ticks = 0;
	window->setVerticalSyncEnabled(true);

    while (this->window->isOpen()) {
		if (clock.getElapsedTime().asMilliseconds() >= time.asMilliseconds()+1000) {
			std::ostringstream ss; 
			ss << (ticks);
			fps.setString("FPS: "+ss.str());
			time = clock.getElapsedTime();
			ticks = 0;
		}
		
		//if (!this->server->isMaster()) this->client->send();
        
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

		this->window->draw(fps);

		this->window->display();
		
		ticks++;
    }

}

int Game::getWindowHeight() {
	return this->windowHeight;
}

int Game::getWindowWidth() {
	return this->windowWidth;
}
