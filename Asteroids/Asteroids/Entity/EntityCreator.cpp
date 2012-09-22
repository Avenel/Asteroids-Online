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
	motion->setDamping(0.06f);
	starship->addUnit(motion);
	
	MotionControl* motionControl = new MotionControl();
	motionControl->setLeft(sf::Keyboard::Left);
	motionControl->setRight(sf::Keyboard::Right);
	motionControl->setAccelerate(sf::Keyboard::Up);
	motionControl->setAccelerationRate(0.6f);
	motionControl->setRotationRate(5.0f);
	starship->addUnit(motionControl);

	Gun* gun = new Gun();
	gun->setBulletRange(100.0f);
	gun->setBulletSpeed(10.0f);
	starship->addUnit(gun);

	GunControl* gunControl = new GunControl();
	gunControl->setShootKey(sf::Keyboard::Space);
	starship->addUnit(gunControl);
	
	StarshipView* starshipView = new StarshipView();
	Display* display = new Display();
	display->setDisplayObject(starshipView);
	starship->addUnit(display);

	return starship;
}

Entity* EntityCreator::createBullet(Gun* gun, Position* startPosition) {
	Entity* bulletEntity = new Entity();

	Bullet* bullet = new Bullet();
	bullet->setRangeRemaining(gun->getBulletRange());
	bulletEntity->addUnit(bullet);
	
	Position* position = new Position(startPosition->getX(), startPosition->getY(), startPosition->getRotation());
	bulletEntity->addUnit(position);
	
	Motion* motion = new Motion();
	float angle = position->getRotation() * M_PI / 180.0f;
	float bulletSpeed = gun->getBulletSpeed();
	motion->setSpeedX(cosf(angle) * bulletSpeed);
	motion->setSpeedY(sinf(angle) * bulletSpeed);
	bulletEntity->addUnit(motion);
	
	BulletView* bulletView = new BulletView();
	Display* display = new Display();
	display->setDisplayObject(bulletView);
	display->setPosition(position->getX(), position->getY());
	bulletEntity->addUnit(display);

	return bulletEntity;
}
