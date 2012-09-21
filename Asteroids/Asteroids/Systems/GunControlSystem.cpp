#include "GunControlSystem.h"

GunControlSystem::GunControlSystem(FamilyManager* familyManager, EntityManager* entityManager)
{
	this->familyManager = familyManager;
	this->entityManager = entityManager;
}

GunControlSystem::~GunControlSystem(void)
{
}

void GunControlSystem::update() {
	list<Node*>* gunControlNodes;
	GunControl* gunControl;
	Position* position;
	Gun* gun;

	gunControlNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::GUN_CONTROL_SYSTEM);

	for (list<Node*>::iterator it = gunControlNodes->begin(); it != gunControlNodes->end(); ++it) {
		position = ((GunControlNode*)(*it))->getPosition();
		gun = ((GunControlNode*)(*it))->getGun();
		gunControl = ((GunControlNode*)(*it))->getGunControl();

		if(sf::Keyboard::isKeyPressed(gunControl->getShootKey())) {
			//cout << "Shoot" << endl;
			this->entityManager->createBullet(gun, position);			
		}
	}
}
