#include "FamilyManager.h"


FamilyManager::FamilyManager(void) {
	this->families = new std::map<Family, std::list<Node*>*>();

}


FamilyManager::~FamilyManager(void) {
	for (std::map<Family, std::list<Node*>*>::iterator it = this->families->begin(); it != this->families->end(); ++it) {
		delete &it;
	}
	delete this->families;
}

void FamilyManager::addMemberToFamily(Family family, Node* node) {
	if ((*this->families)[family] == 0) (*this->families)[family] = new std::list<Node*>();
	(*this->families)[family]->push_back(node);
}

std::list<Node*>* FamilyManager::getMemberOfFamilies(Family family) {
	if ((*this->families)[family] == 0) (*this->families)[family] = new std::list<Node*>();
	return (*this->families)[family];
}

void FamilyManager::addEntityToFamilies(Entity* entity) {
	std::list<Unit*> *units = entity->getAllUnits();

	for (std::list<Unit*>::iterator it = units->begin(); it != units->end(); ++it) {
		/**
			Gefällt mir noch nicht so ganz...
		**/
		switch((*it)->getType()) {
		case(Unit::ASTEROID):
			break;
		case(Unit::DISPLAY):
			addMemberToFamily(Family::RENDER_SYSTEM, new RenderNode(entity));
			break;
		case(Unit::GAMEMAP):
			break;
		case(Unit::GUN):
			break;
		case(Unit::GUNCONTROL):
			break;
		case(Unit::ITEM):
			break;
		case(Unit::MOTION):
			break;
		case(Unit::MOTIONCONTROL):
			break;
		case(Unit::POSITION):
			break;
		case(Unit::STARSHIP):
			break;
		default:
			break;
		}
	}
}

void FamilyManager::removeEntityFromFamilies(Entity* entity) {
	for (std::map<Family, std::list<Node*>*>::iterator it = this->families->begin(); it != this->families->end(); ++it) {
		for (std::list<Node*>::iterator itList = it->second->begin(); itList != it->second->end(); ++itList) {
			if (((*itList)->getEntityId() == entity->getId()) && ((*itList)->getEntityClientId() == entity->getClientId())) it->second->erase(itList);
		}
	}
}