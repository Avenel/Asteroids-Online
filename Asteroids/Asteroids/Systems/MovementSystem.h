#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "SystemCore.h"
#include "FamilyManager.h"
#include <SFML/System/Vector2.hpp>

class MovementSystem : public SystemCore
{
public:
	MovementSystem(void);
	MovementSystem(FamilyManager* familyManager, sf::Vector2u windowSize);
	~MovementSystem(void);
	void damping(Motion* motion);

	void update();

	private:
	FamilyManager* familyManager;
	sf::Vector2u windowSize;
};
