#include "EntityManager.h"


EntityManager::EntityManager(void) {
	this->clientEntities = new std::map<int, std::map<int, Entity*>*>();
	this->entitiesFlat = new list<Entity*>();
	this->familyManager = 0;
}

EntityManager::EntityManager(FamilyManager *familyManager) {
	this->clientEntities = new std::map<int, std::map<int, Entity*>*>();
	this->entitiesFlat = new list<Entity*>();
	this->familyManager = familyManager;
}


EntityManager::~EntityManager(void) {
	delete this->clientEntities;
	delete this->entitiesFlat;
}

void EntityManager::addEntity(Entity *entity) {
	if ((*this->clientEntities)[entity->getClientId()] == 0 ) (*this->clientEntities)[entity->getClientId()] =  new std::map<int, Entity*>();
	(*(*this->clientEntities)[entity->getClientId()])[entity->getId()] = entity;

	// Entity einer Familie hinzufügen
	this->familyManager->addEntityToFamilies(entity);

	this->entitiesFlat->push_back(entity);
}

Entity* EntityManager::getEntity(int id, int clientId) {
	if ((*this->clientEntities)[clientId] == 0) return 0;
	return (*(*this->clientEntities)[clientId])[id];
}

map<int,Entity*>* EntityManager::getClientEntities(int clientId) {
	return (*this->clientEntities)[clientId];
}

void EntityManager::deleteEntity(Entity *entity) {
	(*(*this->clientEntities)[entity->getClientId()]).erase(entity->getId());

	// Leider noch etwas "teuer" ...
	int findId = entity->getId();
	for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
		if ((*it)->getId() == findId) {
			this->entitiesFlat->erase(it);
			delete (*it);
		}
	}

	this->familyManager->removeEntityFromFamilies(entity);
}

list<Entity*>* EntityManager::getAllEntitiesFlat() {
	return this->entitiesFlat;
}

std::map<int, std::map<int, Entity*>*>* EntityManager::getAllEntitiesMap() {
	return this->clientEntities;
}

int EntityManager::getNextId(int clientId) {
	if ((*this->clientEntities)[clientId] == 0 ) return 0;
	return (*this->clientEntities)[clientId]->size();
}

Entity* EntityManager::createStarship() {
	Entity* entity = this->EntityCreator::createStarship();
	this->addEntity(entity);

	return entity;
}

Entity* EntityManager::createBullet(Gun* gun, Position* startPosition) {
	Entity* entity = this->EntityCreator::createBullet(gun, startPosition);
	//entity->setId(this->getNextId(BLA BLA BLA));
	this->addEntity(entity);

	return entity;
}