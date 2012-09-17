#pragma once

#include <SFML/Graphics.hpp>

#include "..\Systems\SystemManager.h"
#include "..\Systems\EntityManager.h"
#include "..\Systems\GameManager.h"
#include "..\Systems\MotionControlSystem.h"
#include "..\Systems\RenderSystem.h"
#include "..\Network\Server.h"
#include "..\Network\Client.h"

using namespace std;

class Game
{
public:
	Game(void);
	~Game(void);

	void startUp();
	void addSystems();
	void run();

private:

	// Systeme
	SystemManager *systemManager;
	EntityManager *entityManager;
	GameManager *gameManager;
	MotionControlSystem *motionControlSystem;
	RenderSystem *renderSystem;
	
	// Netzwerkarchitektur
	Server *server;
	Client *client;

};

