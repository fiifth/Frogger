/*
 * ItemSDL.h
 *
 *  Created on: 18-mrt.-2016
 *      Author: msn-w
 */

#ifndef SDL_ENTITIES_ITEMSDL_H_
#define SDL_ENTITIES_ITEMSDL_H_

#include "Item.h"
#include "SDLdata.h"
#include "SDL.h"
#include "Row.h"
#include <vector>
#include "Animator.h"
namespace frogger_sdl
{
class ItemSDL: public frogger::Item
{
public:
	ItemSDL(SDLdata* sdldata, frogger::Row* row, int x, int y, int w, int h, int ind);
	ItemSDL(SDLdata* sdldata, frogger::Row* row, int ind);
	virtual ~ItemSDL();
	void draw();
private:
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w,
			int h);
	SDLdata* sdldata;
	Animator* ani;
};
}

#endif /* SDL_ENTITIES_ITEMSDL_H_ */
