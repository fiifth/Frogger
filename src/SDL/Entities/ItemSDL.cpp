/*
 * ItemSDL.cpp
 *
 *  Created on: 18-mrt.-2016
 *      Author: msn-w
 */

#include <ItemSDL.h>
#include <iostream>
using namespace frogger_sdl;

frogger_sdl::ItemSDL::ItemSDL(SDLdata* sdldata):sdldata(sdldata)
{
	itemTex=sdldata->getTextureVector('I');
}

ItemSDL::~ItemSDL()
{
	delete (ani);
}



void ItemSDL::draw()
{
	sdldata->renderTexture(itemTex->at(ani->getIndex()), sdldata->getRen(), x, *y, &w, h,row->isDirLeft(), true);
	if (ani->isTurned() && !turned)
	{
		isTurenedByAni = true;
		turned = true;
	}
	else if (isTurenedByAni && turned)
	{
		turned = false;
	}
}


void frogger_sdl::ItemSDL::queryW(int height)
{
	w=sdldata->getDW(itemTex->at(ani->getIndex()), height);
}
