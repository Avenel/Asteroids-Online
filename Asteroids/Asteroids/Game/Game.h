#pragma once

#include <SFML/Graphics.hpp>

#include "..\Systems\SystemManager.h"
#include "..\Systems\FamilyManager.h"
#include "..\Systems\EntityManager.h"
#include "..\Systems\GameManager.h"
#include "..\Systems\MotionControlSystem.h"
#include "..\Systems\RenderSystem.h"
#include "..\Systems\MovementSystem.h"
#include "..\Network\Server.h"
#include "..\Network\Client.h"
#include "..\Entity\EntityCreator.h"

using namespace std;

class Game
{
public:
	Game(void);
	Game(int windowHeight, int windowWidth);
	~Game(void);

	void startUp();
	void addSystems();
	void run();

	int getWindowHeight();
	int getWindowWidth();

private:

	// Systeme
	SystemManager* systemManager;
	FamilyManager* familyManager;
	EntityManager* entityManager;
	GameManager* gameManager;
	MotionControlSystem* motionControlSystem;
	RenderSystem* renderSystem;
	MovementSystem* movementSystem;
	
	// EntityCreator
	EntityCreator* entityCreator;

	// Netzwerkarchitektur
	Server* server;
	Client* client;

	// Window
	int windowHeight;
	int windowWidth;
	sf::RenderWindow *window;
};

