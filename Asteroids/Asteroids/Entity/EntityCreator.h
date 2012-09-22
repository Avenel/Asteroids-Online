#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "../Components/Asteroid.h"
#include "../Components/Bullet.h"
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
#include "../Graphics/BulletView.h"
#include "Entity.h"


class EntityCreator
{
public:
	EntityCreator();
	~EntityCreator(void);
	Entity* createStarship();
	Entity* createBullet(Gun* gun, Position* startPosition);
	void destroyEntity(Entity* entity);

private:
};
