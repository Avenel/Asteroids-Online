#pragma once
#include "../Systems/EntityManager.h"
#include "../Components/Asteroid.h"
#include "../Components/Gun.h"
#include "../Components/GunControl.h"
#include "../Components/Item.h"
#include "../Components/Motion.h"
#include "../Components/MotionControl.h"
#include "../Components/Position.h"
#include "../Components/Starship.h"
#include "../Components/Display.h"
#include "../Graphics/View.h"
#include "../Graphics/StarshipView.h"


class EntityCreator
{
public:
	EntityCreator();
	~EntityCreator(void);
	Entity* createStarship();
	void destroyEntity(Entity* entity);

private:
};
