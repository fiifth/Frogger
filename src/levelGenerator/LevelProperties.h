/*
 * LevelProperties.h
 *
 *  Created on: 23-apr.-2016
 *      Author: msn-w
 */

#ifndef LEVELGENERATOR_LEVELPROPERTIES_H_
#define LEVELGENERATOR_LEVELPROPERTIES_H_
#include "RowProp.h"
#include <vector>
namespace frogger
{
class LevelProperties
{
public:
	LevelProperties(char mode);
	virtual ~LevelProperties();
	void level1();
	const RowProp* getFirstRow() const;
	const RowProp* getLastRow() const;
	const RowProp* getMiddleRow() const;
	const RowProp* getSeg1() const;
	const RowProp* getSeg2() const;
	const RowProp* getSeg3() const;
	const RowProp* getSeg4() const;
	std::vector<int> getVec(int a,int b);
	char getMode() const;
	void setMode(char mode);

private:
	RowProp* firstRow=nullptr;
	RowProp* lastRow=nullptr;
	RowProp* middleRow=nullptr;
	RowProp* seg1=nullptr;
	RowProp* seg2=nullptr;
	RowProp* seg3=nullptr;
	RowProp* seg4=nullptr;
	char mode;
};
}

#endif /* LEVELGENERATOR_LEVELPROPERTIES_H_ */
