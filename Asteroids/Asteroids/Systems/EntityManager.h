#pragma once

#include "..\Entity\Entity.h"
#include "..\Nodes\RenderNode.h"
#include "..\Entity\EntityCreator.h"
#include <list>
#include <map>
#include "FamilyManager.h"

class EntityManager : public EntityCreator
{
public:
	EntityManager(void);
	EntityManager(FamilyManager *familyManager);
	~EntityManager(void);

	void addEntity(Entity *newEntity);
	void deleteEntity(Entity *entity);

	Entity* createStarship();
	Entity* createBullet(Gun* gun, Position* startPosition);

	Entity* getEntity(int id, int clientId);
	std::list<Entity*>* getAllEntitiesFlat();
	std::map<int, std::map<int, Entity*>*>* getAllEntitiesMap();
	std::map<int, Entity*>* getClientEntities(int clientId);

private:
	/** Es gibt 2 Hashmaps:	1) Geordnet nach ClientIds
							2) Geordnet nach Entities
	*/
			//clientid     	entities      
	std::map<int, std::map<int, Entity*>*> *clientEntities;

	int getNextId(int clientId);

	// Verbindung zum FamilyManager
	FamilyManager* familyManager;

	// Flache Hierarchie um schnell alle Entities durchgehen zu können
	list<Entity*> *entitiesFlat;
	list<RenderNode*> *renderNodes;
};