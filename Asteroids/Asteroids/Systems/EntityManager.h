#pragma once

#include "..\Entity\Entity.h"
#include "SystemCore.h"

#include <list>
#include <map>

class EntityManager : public SystemCore
{
public:
	EntityManager(void);
	~EntityManager(void);

	void addEntity(Entity *newEntity);
	void deleteEntity(Entity *entity);

	Entity* getEntity(int id, int clientId, int type);
	list<Entity*>* getAllEntitiesFlat();
	std::map<int, std::map<int, std::map<int, Entity*>*> *>* getAllEntitiesMap();
	map<int, map<int, Entity*>*>* getClientEntities(int clientId);

private:
	/** Es gibt 3 Hashmaps:	1) Geordnet nach ClientIds
							2) Geordnet nach Types
							3) Geordnet nach Entities
	*/
			//clientid     type		entities      
	std::map<int, std::map<int, std::map<int, Entity*>*> *> *clientEntities;

	int getNextId(int clientId, int type);

	// Flache Hierarchie um schnell alle Entities durchgehen zu können
	list<Entity*> *entitiesFlat;
};