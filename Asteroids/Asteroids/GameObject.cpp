#include "GameObject.h"


GameObject::GameObject(void) {
	this->id = 0;
	this->type = 0;
	this->x = 0;
	this->y = 0;
}

GameObject::GameObject(int id, int type) {
	this->id = id;
	this->type = type;
	this->x = 0;
	this->y = 0;
}

GameObject::~GameObject(void){}

void GameObject::refresh(Packet packet){
	packet >> this->x >> this->y;
	cout << "Refresh: " << this->id << ", "<< x <<", "<< y << endl;
}

int GameObject::getId() { 
	return this->id;
}

int GameObject::getX() {
	return this->x;
}

int GameObject::getY() {
	return this->y;
}

void GameObject::setId(int id) {
	this->id = id;
}

void GameObject::setType(int type) {
	this->type = type;
}

int GameObject::getType() {
	return this->type;
}

void GameObject::setX(int x) {
	this->x = x;
}

void GameObject::setY(int y) {
	this->y = y;
}

Packet GameObject::getPacket(int clientId) {

	if (clientId != 0) this->clientId = clientId;

	Packet packet;
	char* uuid_str;
	packet << this->id << this->clientId << this->type << this->x << this->y;
	return packet;
}

int GameObject::getClientId() {
	return this->clientId;
}