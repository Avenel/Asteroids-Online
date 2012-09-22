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
	//Entity zu RenderNode-Family hinzufuegen
	if(RenderNode().isEntityMember(entity)) {
		addMemberToFamily(Family::RENDER_SYSTEM, new RenderNode(entity));
	}

	//Entity zu MotionControlNode-Family hinzufuegen
	if(MotionControlNode().isEntityMember(entity)) {
		addMemberToFamily(Family::MOTION_CONTROL_SYSTEM, new MotionControlNode(entity));
	}

	//Entity zu GunControlNode-Family hinzufuegen
	if(GunControlNode().isEntityMember(entity)) {
		addMemberToFamily(Family::GUN_CONTROL_SYSTEM, new GunControlNode(entity));
	}

	//Entity zu MovementNode-Family hinzufuegen
	if(MovementNode().isEntityMember(entity)) {
		addMemberToFamily(Family::MOVEMENT_SYSTEM, new MovementNode(entity));
	}
}

void FamilyManager::removeEntityFromFamilies(Entity* entity) {
	for (std::map<Family, std::list<Node*>*>::iterator it = this->families->begin(); it != this->families->end(); ++it) {
		for (std::list<Node*>::iterator itList = it->second->begin(); itList != it->second->end(); ++itList) {
			if (((*itList)->getEntityId() == entity->getId()) && ((*itList)->getEntityClientId() == entity->getClientId())) it->second->erase(itList);
		}
	}
}