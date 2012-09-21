#include "GunControlNode.h"


GunControlNode::GunControlNode(void)
{
}

GunControlNode::GunControlNode(Entity* entity)
{
	this->Node::Node(entity);
	this->addEntity();
}

GunControlNode::~GunControlNode(void)
{
}

bool GunControlNode::isEntityMember(Entity* entity) {
	return (entity->hasComponent(Unit::GUN) && entity->hasComponent(Unit::GUNCONTROL) && entity->hasComponent(Unit::POSITION));
}

void GunControlNode::addEntity() {
	this->gun = (Gun*)this->entity->getComponent(Unit::GUN);
	this->gunControl = (GunControl*)this->entity->getComponent(Unit::GUNCONTROL);
	this->position = (Position*)this->entity->getComponent(Unit::POSITION);
}

Position* GunControlNode::getPosition() {
	return this->position;
}

Gun* GunControlNode::getGun() {
	return this->gun;
}

GunControl* GunControlNode::getGunControl() {
	return this->gunControl;
}
