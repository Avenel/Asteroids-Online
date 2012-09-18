#pragma once

#include <SFML/Graphics.hpp>
#include "SystemCore.h"
#include "FamilyManager.h"

class RenderSystem : public SystemCore
{
public:
	RenderSystem();
	RenderSystem(FamilyManager* familyManager, sf::RenderWindow *window);
	~RenderSystem(void);
	void update();
private:
	// Window
	sf::RenderWindow *window;
	FamilyManager* familyManager;
};
