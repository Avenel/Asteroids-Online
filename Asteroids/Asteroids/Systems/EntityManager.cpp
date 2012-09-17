#include "EntityManager.h"


EntityManager::EntityManager(void) {
	this->clientEntities = new std::map<int, std::map<int, std::map<int, Entity*>*> *>();
	this->entitiesFlat = new list<Entity*>();
}


EntityManager::~EntityManager(void) {
	delete this->clientEntities;
	delete this->entitiesFlat;
}

void EntityManager::addEntity(Entity *entity) {
	(*(*(*this->clientEntities)[entity->getClientId()])[entity->getType()])[entity->getId()] = entity;
	this->entitiesFlat->push_back(entity);
}

Entity* EntityManager::getEntity(int id, int clientId, int type) {
	return (*(*(*this->clientEntities)[clientId])[type])[id];
}

map<int, map<int, Entity*>*>* EntityManager::getClientEntities(int clientId) {
	return (*this->clientEntities)[clientId];
}

void EntityManager::deleteEntity(Entity *entity) {
	(*(*(*this->clientEntities)[entity->getClientId()])[entity->getType()]).erase(entity->getId());

	// Leider noch etwas "teuer" ...
	int findId = entity->getId();
	for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
		if ((*it)->getId() == findId) {
			this->entitiesFlat->erase(it);
		}
	}
}
