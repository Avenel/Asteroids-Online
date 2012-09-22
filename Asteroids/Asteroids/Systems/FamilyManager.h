#pragma once

#include "..\Nodes\Node.h"
#include "..\Nodes\RenderNode.h"
#include "..\Nodes\MotionControlNode.h"
#include "..\Nodes\GunControlNode.h"
#include "..\Nodes\MovementNode.h"
#include <list>

class FamilyManager
{
public:

	enum Family{
		GAME_MANAGER,
		MOTION_CONTROL_SYSTEM,
		RENDER_SYSTEM,
		MOVEMENT_SYSTEM,
		GUN_CONTROL_SYSTEM
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

