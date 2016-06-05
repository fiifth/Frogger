/*
 * SDLstuff.h
 *
 *  Created on: 7-mrt.-2016
 *      Author: msn-w
 */

#ifndef SDLSTUFF_H_
#define SDLSTUFF_H_
#include "SDL.h"
#include <vector>
#include "Animator.h"
#include <string>
namespace frogger_sdl
{
	class SDLdata
	{
		public:
			SDLdata();
			virtual ~SDLdata();
			void setBackground(SDL_Texture* texB);
			void updateScreen();
			SDL_Renderer* getRen();
			void setRen(SDL_Renderer* rende);
			void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int* w, int h, int angle, bool ratio);
			int getDW(SDL_Texture* tex, int h);
			void createTextures();
			std::vector<SDL_Texture*> getBackTextures();
			void setScreenDimension(int* gameWidth, int* gameHeight);
			Animator getAnimator(std::vector<int> indexes,std::vector<int> ratio);
			Animator getItemAni(int ind);
			Animator getLaneAni(int ind);
			Animator getObstiAni(int ind);
			Animator getPlayerAni(int ind);
			Animator getProjAni(int ind);
			int* getScrH() const;
			void setScreenHeight(int* screenHeight);
			int* getScrW() const;
			void setScreenWidth(int* screenWidth);
			std::vector<SDL_Texture*>* getMenuTextures();
			SDL_Texture* getLine();
			void deleteTextures(std::vector<SDL_Texture*> textureVector);
			void fillTextureVectors(std::vector<SDL_Texture*>* textureVector,std::string prefix,int endNumber);
			std::vector<SDL_Texture*>* getTextureVector(char type);

		protected:
			int* screenWidth=nullptr;
			int* screenHeight=nullptr;
			SDL_Renderer* re=nullptr;
			SDL_Texture* line=nullptr;

			std::vector<SDL_Texture*> menuTextures;
			std::vector<SDL_Texture*> backTex;
			std::vector<Animator> obstiAni;
			std::vector<Animator> laneAni;
			std::vector<Animator> playerAni;
			std::vector<Animator> itemAni;
			std::vector<Animator> projAni;
			std::vector<SDL_Texture*> playerTex;
			std::vector<SDL_Texture*> ObstTex;
			std::vector<SDL_Texture*> laneTex;
			std::vector<SDL_Texture*> itemTex;
			std::vector<SDL_Texture*> projTex;

	};
}

#endif /* SDLSTUFF_H_ */
