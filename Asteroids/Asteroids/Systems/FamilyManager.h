#pragma once

#include "..\Nodes\Node.h"
#include "..\Nodes\RenderNode.h"

class FamilyManager
{
public:

	enum Family{
		GAME_MANAGER,
		MOTION_CONTROL_SYSTEM,
		RENDER_SYSTEM
	};

	FamilyManager(void);
	~FamilyManager(void);

	void addEntityToFamilies(Entity* entity);
	void addMemberToFamily(Family family, Node* node);
	std::list<Node*>* getMemberOfFamilies(Family family);

	void removeEntityFromFamilies(Entity* entity);

private:
	std::map<Family, std::list<Node*>*> *families;

};

