#include "EntityCreator.h"


EntityCreator::EntityCreator()
{
}


EntityCreator::~EntityCreator(void)
{
}

Entity* EntityCreator::createStarship() {
	Entity* starship = new Entity();
	
	Position* position = new Position(0, 0);
	starship->addUnit(position);
	
	Starship* starship_unit = new Starship();
	starship->addUnit(starship_unit);

	Motion* motion = new Motion();
	starship->addUnit(motion);
	
	MotionControl* motionControl = new MotionControl();
	starship->addUnit(motionControl);

	Gun* gun = new Gun();
	starship->addUnit(gun);

	GunControl* gunControl = new GunControl();
	starship->addUnit(gunControl);
	
	StarshipView* starshipView = new StarshipView();
	Display* display = new Display();
	display->setDisplayObject(starshipView);
	starship->addUnit(display);

	return starship;
}