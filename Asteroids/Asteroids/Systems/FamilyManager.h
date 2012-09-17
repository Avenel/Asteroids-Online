#pragma once

#include "..\Nodes\Node.h"

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

	void addMemberToFamily(Family family, Node* node);
	std::list<Node*>* getMemberOfFamilies(Family family);

private:
	std::map<Family, std::list<Node*>*> *families;

};

