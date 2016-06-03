/*
 * LaneSDL.h
 *
 *  Created on: 18-mrt.-2016
 *      Author: msn-w
 */

#ifndef SDL_ENTITIES_LANESDL_H_
#define SDL_ENTITIES_LANESDL_H_
#include "Lane.h"
#include "SDLdata.h"
#include "Row.h"
#include "SDL.h"
#include <vector>
#include "Animator.h"
#include "Factory.h"
namespace frogger_sdl
{
class LaneSDL: public frogger::Lane
{
public:
	LaneSDL(SDLdata* sdldata, frogger::Row* row, frogger::Factory* F,bool visible, int x, int y, int w, int h);
	LaneSDL(SDLdata* sdldata, frogger::Row* row, frogger::Factory* F,bool visible);
	virtual ~LaneSDL();
	void draw();
private:

	SDLdata* sdldata;
	Animator* ani;
};
}

#endif /* SDL_ENTITIES_LANESDL_H_ */
