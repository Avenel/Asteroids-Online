#include "FamilyManager.h"


FamilyManager::FamilyManager(void) {
	this->families = new std::map<Family, std::list<Node*>*>();
	
	(*this->families)[Family::GAME_MANAGER] = new std::list<Node*>();
	(*this->families)[Family::MOTION_CONTROL_SYSTEM] = new std::list<Node*>();
	(*this->families)[Family::RENDER_SYSTEM] = new std::list<Node*>();
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
