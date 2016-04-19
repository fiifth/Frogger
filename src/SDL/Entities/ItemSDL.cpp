/*
 * ItemSDL.cpp
 *
 *  Created on: 18-mrt.-2016
 *      Author: msn-w
 */

#include <ItemSDL.h>
#include "Row.h"
#include <stdlib.h>
#include <iostream>


ItemSDL::ItemSDL(SDLdata* sdldata,Row* row,int x,int y,int w,int h,int ind) :sdldata(sdldata)
{
	ani=sdldata->getItemAni(ind).clone();
	setRow(row);
	setSpeed(row->getSpeed());
	setDirection(row->isDirLeft()?4:2);
	divider=row->getDivider();
	setSize(0,h);
	setScreenSize(sdldata->getScreenWidth(),sdldata->getScreenHeight());
	int wn=0,hn=h;
	sdldata->getDependWAndH(ani->getTexture(),&wn, &hn);
	setSize(wn,hn);
	setLocation(x,y);
}

ItemSDL::~ItemSDL() {
	std::cout<<"hellooooooo"<<std::endl;
	delete(ani);
}

void ItemSDL::draw()
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
}

ItemSDL::ItemSDL(SDLdata* sdldata, Row* row,int ind) :sdldata(sdldata)
{
	ani=sdldata->getItemAni(ind).clone();
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
