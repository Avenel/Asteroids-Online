#pragma once
#include "Node.h"
#include "../Components/GunControl.h"
#include "../Components/Gun.h"
#include "../Components/Position.h"

class GunControlNode : public Node
{
public:
	GunControlNode(void);
	GunControlNode(Entity* entity);
	~GunControlNode(void);

	Position* getPosition();
	Gun* getGun();
	GunControl* getGunControl();

	static bool isEntityMember(Entity* entity);
	void addEntity();

private:
	Position* position;
	GunControl* gunControl;
	Gun* gun;
};
