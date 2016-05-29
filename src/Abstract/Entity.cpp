/*
 * Entity.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: msn-w
 */

#include "Entity.h"
#include "Props.h"
#include "Projectile.h"
using namespace frogger;
Entity::Entity() :
		F(nullptr)
{
	x = 30;
	*y = 30;
	w = 10;
	h = 10;
	screenWidth = 640;
	screenHeight = 480;
	*speed = 50;
}

Entity::~Entity()
{
}

void Entity::move(int deltaX, int deltaY, bool leaveScreen)
{
	int leftLimit, rightLimit, upperLimit, lowerlimit;
	leftLimit = leaveScreen ? -getWidth() * 4 : 0;
	rightLimit = leaveScreen ? screenWidth + getWidth() * 4 : screenWidth;
	upperLimit = leaveScreen ? -getWidth() * 4 : 0;
	lowerlimit = leaveScreen ? screenHeight + getWidth() * 4 : screenHeight;
	if (((x + deltaX + w) <= rightLimit) && (x + deltaX) >= leftLimit)
	{
		x = x + deltaX;
	}
	if (((*y + deltaY + h) <= lowerlimit) && (*y + deltaY) >= upperLimit)
	{
		*y = *y + deltaY;
	}
}

void Entity::setSize(int wNew, int hNew)
{
	w = wNew;
	h = hNew;
}
void Entity::setLocation(int xNew, int yNew)
{
	x = xNew;
	*y = yNew;
}
void Entity::setScreenSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}
bool Entity::inframe()
{
	return ((x < (screenWidth + (3 * w)) && x > (0 - (3 * w)))
			&& ((*y <= screenHeight + h*4) && (*y >= (0 - h*4))));
}

int Entity::getH() const
{
	return h;
}

int Entity::getW() const
{
	return w;
}

int Entity::getX() const
{
	return x;
}

int Entity::getY() const
{
	return *y;
}

int Entity::getHeight() const
{
	return screenHeight;
}

int Entity::getWidth() const
{
	return screenWidth;
}

int Entity::getSpeed() const
{
	return *speed;
}


char Entity::getDirection() const
{
	return *direction;
}


void Entity::setF(Factory* f)
{
	F = f;
}

bool Entity::drawMoveRemove::operator ()(Props* prop)
{
	bool temp = false;
	if (!prop->inframe())
	{
		temp = true;
		delete (prop);
	}
	else
	{
		prop->moveForward();
		if (prop->isVisible())
			prop->draw();

	}
	return temp;
}

bool Entity::colli(Entity* entity)
{
	return (colli2(this,entity)||colli2(entity,this));
}

void frogger::Entity::setYPointer(int* y)
{
	this->y=y;
}

bool Entity::colli2(Entity* entity1,Entity* entity2)
{
	int ay1=entity1->getY();
	int ay2=entity1->getY()+entity1->getH();
	int by1=entity2->getY();
	int by2=entity2->getY()+entity2->getH();
	int ax1=entity1->getX();
	int ax2=entity1->getX()+entity1->getW();
	int bx1=entity2->getX();
	int bx2=entity2->getX()+entity2->getW();

	return (((ay1 >= by1 && ay1 < by2) || (ay2 > by1 && ay2 <= by2))
		&& ((ax1 >= bx1 && ax1 <= bx2) || (ax2 >= bx1&& ax2 <= bx2)));
}
