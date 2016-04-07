/*
 * ProjectileSDL.cpp
 *
 *  Created on: 4-apr.-2016
 *      Author: msn-w
 */

#include <ProjectileSDL.h>

ProjectileSDL::ProjectileSDL(SDLdata* sdldata,int direction,int Xstart,int Ystart,int size,int speed):sdldata(sdldata) {
	//1=up,2=right,3=down,4=left;
	ani=sdldata->getItemAni().clone();
		setDirection(direction);
		setSpeed(speed);
		setSize(0,size);
		setScreenSize(sdldata->getScreenWidth(),sdldata->getScreenHeight());
		int wn=0,hn=size;
		sdldata->getDependWAndH(ani->getTexture(),&wn, &hn);
		setSize(wn,hn);
		setLocation(Xstart,Ystart);
}

ProjectileSDL::~ProjectileSDL() {
	// TODO Auto-generated destructor stub
}

void ProjectileSDL::draw()
{//int direction=0;//1=up,2=right,3=down,4=left;
	int angle=0;
	angle=(getDirection()==2)?90:angle;
	angle=(getDirection()==3)?180:angle;
	angle=(getDirection()==4)?270:angle;
	sdldata->renderTexture(ani->getTexture(),sdldata->getRen(),x,y,&w,&h,angle);
}

