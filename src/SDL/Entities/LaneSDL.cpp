/*
 * LaneSDL.cpp
 *
 *  Created on: 18-mrt.-2016
 *      Author: msn-w
 */

#include <LaneSDL.h>
#include "Row.h"
#include <stdlib.h>
#include <iostream>

 LaneSDL::LaneSDL(SDLdata* sdldata,Row* row,Factory* F,int x,int y,int w,int h) :sdldata(sdldata)
{
	 setF(F);
	ani=sdldata->getLaneAni().clone();
	setRow(row);
	setDirection(row->isDirLeft()?4:2);
	setSpeed(row->getSpeed());
	divider=row->getDivider();
	setSize(0,h);
	setScreenSize(sdldata->getScreenWidth(),sdldata->getScreenHeight());
	int wn=0,hn=h;
	sdldata->getDependWAndH(ani->getTexture(),&wn, &hn);
	setSize(wn,hn);
	setLocation(x,row->getLocY());
}
LaneSDL::~LaneSDL() {
	delete(ani);
}

LaneSDL::LaneSDL(SDLdata* sdldata, Row* row,Factory* F) :sdldata(sdldata)
{
	 setF(F);
	ani=sdldata->getLaneAni().clone();
	setRow(row);
	//1=up,2=right,3=down,4=left;
		setDirection(row->isDirLeft()?4:2);
	setSpeed(row->getSpeed());
	divider=row->getDivider();
	setSize(0,row->getHeight());
	setScreenSize(sdldata->getScreenWidth(),sdldata->getScreenHeight());
	int wn=0,hn=row->getHeight();
	sdldata->getDependWAndH(ani->getTexture(),&wn, &hn);
	setSize(wn,hn);
	int xloc=row->isDirLeft()?screenWidth:-getW();
	setLocation(xloc,row->getLocY());
}

void LaneSDL::draw()
{
	int angle=0;
	angle=row->isDirLeft()?1:0;
	sdldata->renderTexture(ani->getTexture(),sdldata->getRen(),x,y,&w,&h,angle);

	if(ani->isTurned()&&!turned)
	{
		isTurenedByAni=true;
		turned=true;
	}
	else if (isTurenedByAni&&turned)
	{
		turned=false;
	}
	itemList.remove_if(drawMoveRemove());
}
