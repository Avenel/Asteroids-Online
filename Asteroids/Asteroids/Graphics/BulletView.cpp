#include "BulletView.h"

BulletView::BulletView(float radius)
{
	this->radius = radius;
	this->createBulletPolygon();
}


BulletView::~BulletView(void)
{
}

void BulletView::draw(sf::RenderWindow *target, sf::RenderStates &states) {
	target->draw((*this->bulletPolygon));
}

void BulletView::setPosition(float x, float y) {
	this->bulletPolygon->setPosition(x, y);
}

void BulletView::setRotation(float degree) {
}

void BulletView::createBulletPolygon() {
	this->bulletPolygon = new sf::CircleShape(this->radius);
	this->bulletPolygon->setFillColor(sf::Color::White);
}