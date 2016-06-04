/*
 * LevelProperties.cpp
 *
 *  Created on: 23-apr.-2016
 *      Author: msn-w
 */

#include <levelGenerator/LevelProperties.h>
using namespace frogger;

LevelProperties::LevelProperties(char mode, char difficulty) :
		mode(mode), difficulty(difficulty)
{
	level=1;

	firstRow = new RowProp(0, 0, 'A', mode, 0, 0, 0, true, false, { 1 }, { 0 }, { 10, 20, 70 });
	lastRow = new RowProp(0, 0, 'E', mode, 100, 100, 0, true, false, getVec(10, 11), { 2 }, { 10, 20, 70 });
	middleRow = new RowProp(0, 0, 'D', mode, 50, 50, 0, true, false, getVec(10, 11), { 0 }, { 10, 20, 70 });

	if (difficulty == 'E')
		easyLevel();
	else if (difficulty == 'M')
		mediumLevel();
	else if (difficulty == 'H')
		hardLevel();
}

LevelProperties::~LevelProperties()
{
	delete(firstRow);
	delete(lastRow);
	delete(middleRow);
	delete(seg1);
	delete(seg2);
	delete(seg3);
	delete(seg4);
}

void LevelProperties::easyLevel()
{
	seg1 = new RowProp(1, 0, 'B', mode, 40, 30, 0, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 30, 70 });
	seg2 = new RowProp(1, 0, 'B', mode, 50, 10, 20, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg3 = new RowProp(1, 0, 'C', mode, 40, 30, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg4 = new RowProp(1, 0, 'C', mode, 50, 10, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
}
void frogger::LevelProperties::mediumLevel()
{
	seg1 = new RowProp(2, 0, 'B', mode, 40, 30, 0, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg2 = new RowProp(2, 0, 'B', mode, 50, 10, 20, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg3 = new RowProp(2, 0, 'C', mode, 40, 30, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg4 = new RowProp(2, 0, 'C', mode, 50, 10, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
}

void frogger::LevelProperties::hardLevel()
{
	seg1 = new RowProp(2, 0, 'B', mode, 40, 30, 0, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg2 = new RowProp(2, 0, 'B', mode, 50, 10, 20, true, false, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg3 = new RowProp(2, 0, 'C', mode, 40, 30, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
	seg4 = new RowProp(2, 0, 'C', mode, 50, 10, 70, false, true, getVec(0, 8), {0, 3, 4, 5 }, { 10, 20, 70 });
}

RowProp* LevelProperties::getFirstRow()
{
	return firstRow;
}

RowProp* LevelProperties::getLastRow()
{
	return lastRow;
}

RowProp* LevelProperties::getMiddleRow()
{
	return middleRow;
}

RowProp* LevelProperties::getSeg1()
{
	return seg1;
}

RowProp* LevelProperties::getSeg2()
{
	return seg2;
}

RowProp* LevelProperties::getSeg3()
{
	return seg3;
}

RowProp* LevelProperties::getSeg4()
{
	return seg4;
}

std::vector<int> LevelProperties::getVec(int a, int b)
{
	std::vector<int> temp;
	for (int i = a; i <= b; i++)
	{
		temp.push_back(i);
	}
	return temp;

}

char LevelProperties::getMode() const
{
	return mode;
}

void LevelProperties::setMode(char mode)
{
	this->mode = mode;
}

RowProp* LevelProperties::getRandomRow()
{
	int temp = rand() % 110;
	if (temp < 25)
		return seg1;
	else if (temp < 50)
		return seg2;
	else if (temp < 75)
		return seg3;
	else if (temp < 100)
		return seg4;
	else
		return middleRow;
}

void frogger::LevelProperties::levelUp()
{
	//int deltaSpe, int deltaDiv,	int deltaObsRate, int deltaItemRate, int deltaShootRate
	level = level + 1;

	if (level == 2)
	{
		seg1->increaseProp(0, 0, 10, -1, 5);
		seg2->increaseProp(0, 0, 10, -1, 5);
		seg3->increaseProp(0, 0, 10, -1, 5);
		seg4->increaseProp(0, 0, 10, -1, 5);
	}
	else if (level == 3)
	{
		seg1->increaseProp(1, 0, 0, -1, 0);
		seg2->increaseProp(1, 0, 0, -1, 0);
		seg3->increaseProp(1, 0, 0, -1, 0);
		seg4->increaseProp(1, 0, 0, -1, 0);
	}
	else if (level == 4)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 5)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 6)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 7)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 8)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 9)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 10)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 11)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 12)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 13)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 14)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
	else if (level == 15)
	{
		seg1->increaseProp(0, 0, 0, 0, 0);
		seg2->increaseProp(0, 0, 0, 0, 0);
		seg3->increaseProp(0, 0, 0, 0, 0);
		seg4->increaseProp(0, 0, 0, 0, 0);
	}
}

char frogger::LevelProperties::getDifficulty()
{
	return difficulty;
}
