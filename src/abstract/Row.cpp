/*
 * Row.cpp
 *
 * Used by prop objects. This object is a collection of properties that will be used by props.
 *
 *  Created on: 12-mrt.-2016
 *      Author: Kwinten
 */

#include <abstract/Row.h>
#include <stdlib.h>
using namespace frogger;

Row::Row(char direction, int locY, int height, int number,RowProp* rowProperties) :
		direction(direction), locY(locY), height(height), number(number),
		rowProperties(rowProperties)
{
}

Row::~Row()
{
}

bool Row::isDirLeft() const
{
	return direction == 'L';
}

int* Row::getLocY()
{
	return &locY;
}

int Row::getNumber() const
{
	return number;
}

int Row::getHeight() const
{
	return height;
}

void Row::setLocY(int NewlocY)
{
	locY = NewlocY;
}
Row* Row::clone()
{
	return new Row(*this);
}

bool Row::isLaneVis() const
{
	return rowProperties->getLaneVis();
}

bool Row::isObstacleVis() const
{
	return rowProperties->getObstacleVis();
}

RowProp* Row::getRowProperties()
{
	return rowProperties;
}

int Row::getRandomObsInd()
{
	return rowProperties->getObstIndexes().at(
			rand() % rowProperties->getObstIndexes().size());
}

int Row::getRandomLaneInd()
{
	return rowProperties->getLaneIndexes().at(
			rand() % rowProperties->getLaneIndexes().size());
}

void Row::setRowProperties(RowProp* rowProp)
{
	rowProperties = rowProp;
}

char* frogger::Row::getDirection()
{
	return &direction;
}
