/*
 * Game.cpp
 *
 *  Created on: 22 Feb 2016
 *      
 */


#include "Game.h"

#include "SDLdata.h"
#include "Factory.h"
#include "Window.h"
#include "Events.h"
#include <iostream>
#include <string>
#include "Row.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime>
#include <ratio>
#include <chrono>
#include "Projectile.h"
#include <Obstacle.h>
#include <Player.h>

using namespace std;
using namespace std::chrono;


Game::Game(Factory* F)
{
	srand (time(NULL));
	int rowHeight=50;
	int difficultyRows=1;
	int WindowHeight=520;
	int WindowWidth=700;
	int difficulty=90;
	int dataWindowHeightDesired=20;
	int dataWindowHeight=((WindowHeight-dataWindowHeightDesired)%rowHeight)+dataWindowHeightDesired;
	int gameWindowHeight=WindowHeight-dataWindowHeight;
	int gameWindowWidth=WindowWidth;
	int plStartW=rowHeight,plStartH=rowHeight,plStartSpeed=rowHeight;
	int plStartX=(gameWindowWidth/2),plStartY=(gameWindowHeight-plStartW);
	string keyStroke;
	vector<Row*> rowsR;
	vector<list<Props*>> propsOnRowR;
	list<Projectile*>projectilesR;
	list<Projectile*>*projectiles=&projectilesR;
	vector<Row*>* rows=&rowsR;
	vector<list<Props*>>* propsOnRow=&propsOnRowR;
	list<Player*> playersR;
	list<Player*>* players=&playersR;


	Window* win=F->createWindow();
	win->makeWindow(WindowWidth,WindowHeight,dataWindowHeight,"frogger");

	Player* player=F->createPlayer(plStartX,plStartY,plStartW,plStartH,plStartSpeed,rowHeight);
	players->push_back(player);
	Events* event=F->createEvents();

	rowGenerator(rowHeight,gameWindowHeight,difficultyRows,F,rows,propsOnRow);

	fillEnemyList(F,rows,propsOnRow, difficulty,WindowWidth);

	char state='B';
	while(true)
	{
		keyStroke=event->getEvent();
		switch(state)
		{
		//----------------------------------------------------------------------------------------------------
			case 'A'  :
				if (keyStroke!="")
				{
					player->takeAction(keyStroke);
					if (keyStroke=="Escape")
						return;
					else if (keyStroke=="Space")
					{
						if (player->getProjectiles()>0)
						{
						projectiles->push_back(F->createProjectile(player,5));
						player->addProjectiles(-1);
						}
					}
				}

				win->generateBackground(rows);

				propsGenerator(F,difficulty,rows,propsOnRow);

				if (collisionDetection(propsOnRow,projectiles,players)==1)
						state='B';
				else
				{
					drawGameElements(propsOnRow,projectiles, players,rows);
				}

				win->dislayData(player->getScore(),player->getLife(),player->getProjectiles(),player->getRemainingTime());
				win->updateScreen();
				break;

				//----------------------------------------------------------------------------------------------------
			case 'B':
				win->setBackground();
				win->displayHighScore(player->getHighScore().at(0),
						player->getHighScore().at(1),
						player->getHighScore().at(2),
						player->getHighScore().at(3));

				if (keyStroke!="")
				{
					if (keyStroke=="Space")
					{
						player->resetRemainingTime();
						state='A';
						win->setBackground();
					}
					else if (keyStroke=="Escape")
						return;
				}
				win->updateScreen();
				break;
			}
	}
}

Game::~Game() {}

void Game::rowGenerator(int rowHeight,int screenHight,int difficultyRows,Factory* F,vector<Row*>* rows,vector<list<Props*>>* propsOnRow)
{
	int maxSpeed=3;
	int numberOfRows=(screenHight)/rowHeight;
	int mode=3;
	list<Props*> enemies;
	bool dir=true;//(rand() %2)>0)
	if (mode==1)
	{
		for (int n=0; n<numberOfRows; n++)
		{
			int speed=((rand()%(numberOfRows-n))+1)*difficultyRows;
			speed=speed>maxSpeed?maxSpeed:speed;
			speed=(n==0||n==numberOfRows-1)?0:speed;
			rows->push_back(F->createRow(((rand() %10)>5),speed,(n*rowHeight),rowHeight,n));
			propsOnRow->push_back(enemies);
		}
	}
	else if (mode==2)
	{
		for (int n=0; n<numberOfRows; n++)
		{
			int speed=((rand()%(numberOfRows-n))+1)*difficultyRows;
			speed=speed>maxSpeed?maxSpeed:speed;
			speed=(n==0||n==numberOfRows-1)?0:speed;
			rows->push_back(F->createRow(((rand() %10)>5),speed,(n*rowHeight),rowHeight,n));
			rows->back()->setLaneRow(true);
			propsOnRow->push_back(enemies);
		}
	}
	else if (mode==3)
		{
			for (int n=0; n<numberOfRows; n++)
			{
				list<Props*> enemiies;
				int speed=2;
				speed=(n==0||n==numberOfRows-1)?0:speed;
				rows->push_back(F->createRow(dir,speed,(n*rowHeight),rowHeight,n));
				rows->back()->setLaneRow(n<(numberOfRows/2));
				propsOnRow->push_back(enemies);
				dir=not(dir);
			}
		}
}
void Game::propsGenerator(Factory* F,int difficulty,vector<Row*>* rows,vector<list<Props*>>* propsOnRow)
{
	for(Row* row:*rows)
	{
		if((row->getNumber()!=0)&&(row->getNumber()!=((rows->size())-1)))
		{
			list<Props*>* PreProp=&propsOnRow->at(row->getNumber());
			if((PreProp->empty())||((PreProp->front())->isRoom()))
			{
				Props* prop;
				if(obsOrLane(PreProp,true,row->isLaneRow(),difficulty))
				{
					prop=F->createObstacle(row);
					prop->setVisible(!row->isLaneRow());
				}
				else
				{
					prop=F->createLane(row);
					prop->setVisible(row->isLaneRow());

				}
				propsOnRow->at(row->getNumber()).push_front(prop);
			}
			bool roomOnLane=PreProp->front()->roomForItem();
			bool noItemYet=PreProp->back()->itemAbsent();
			if (roomOnLane&&noItemYet&&(rand()%1000>995))
			{
				Props* propBonus=F->createItem(row);
				propsOnRow->at(row->getNumber()).push_back(propBonus);
			}
			if(rand()%1000>998)
			{
				Props* randomObstable=getRandomObst(PreProp);
				if (randomObstable!=nullptr)
				{
					Props* projec=F->createProjectile(randomObstable,5);
					propsOnRow->at(row->getNumber()).push_back(projec);
				}
			}
		}
	}
}


int Game::collisionDetection(vector<list<Props*>>* propsOnRow,list<Projectile*>*projectiles,list<Player*>* players)
{
	int dete=false;
	for (list<Props*> temp:*propsOnRow)
	{
		for(Props* temp2:temp)
		{
			for (Projectile* proj:*projectiles)
			{
				//TODO use remove if
				if(temp2->isVisible()&&temp2->coll(proj,true))
				{
					temp2->setVisible(false);
					temp2->setTurned(true);
					delete (proj);
					projectiles->remove(proj);
				}
			}

			int effect=temp2->coll(players->back(),true);
			if(effect>1)
			{
				propsOnRow->at(temp2->getRow()->getNumber()).remove(temp2);
				delete(temp2);
				dete=effect;
				players->back()->addScore(1);
				players->back()->addProjectiles(1);
			}
			else if (effect==1||players->back()->getRemainingTime()==0)
			{
				return players->back()->hit();
			}
		}
	}
	return dete;
}

void Game::fillEnemyList(Factory* F,vector<Row*>* rows, vector<list<Props*>>* propsOnRow, int difficulty,int screenWidth)
{
	list<Props*> listOfProps;
	for(Row* row:*rows)
	{
		int x=0;
		while(x<screenWidth)
		{
			if((row->getNumber()!=0)&&(row->getNumber()!=(rows->size()-1)))
			{
				list<Props*>* PreProp=&propsOnRow->at(row->getNumber());
				Props* prop;
				if(obsOrLane(PreProp,row->isDirLeft(),row->isLaneRow(),difficulty))
				{
					prop=F->createObstacle(row,x,5,0,row->getHeight());
					prop->setVisible(!row->isLaneRow());
				}
				else
				{
					prop=F->createLane(row,x,5,0,row->getHeight());
					prop->setVisible(row->isLaneRow());

				}
				if(row->isDirLeft())
					propsOnRow->at(row->getNumber()).push_front(prop);
				else
					propsOnRow->at(row->getNumber()).push_back(prop);

				x=prop->getW()+x;
			}
			else
				x=screenWidth;
		}
	}
}

void Game::drawGameElements(std::vector<std::list<Props*>>* propsOnRow,
		list<Projectile*>* projectiles, list<Player*>* players,vector<Row*>* rows) {
int i=0;

	for (list<Props*> temp:*propsOnRow)
	{
		propsOnRow->at(i).remove_if(drawMoveRemove());
		i++;
	}

	projectiles->remove_if(drawMoveRemove());

	for(Player* player:*players)
	{
		int row=player->getY()/player->getH(); //TODO instread of getH search for row height
		if(rows->at(row)->isLaneRow())
			player->followRow(rows->at(row));
		if(row==0)
		{
			player->addScore(100);
			player->resetPosition();
		}
		player->draw();
	}
}

bool Game::obsOrLane(list<Props*>* PreProp,bool frontOrBack,bool laneRow, int difficulty)
{
	int number=rand()%100;
	if (frontOrBack)
		return ((laneRow&&PreProp->front()->isVisible())||((number>difficulty)&&!PreProp->front()->isVisible()));
	else
		return ((laneRow&&PreProp->back()->isVisible())||((number>difficulty)&&!PreProp->back()->isVisible()));
}

Props* Game::getRandomObst(list<Props*>* PreProp)
{
	Props* prop;
	vector<Props*> temp;
	for(Props* pro:*PreProp)
	{
		Row* row=pro->getRow();
		if(row!=nullptr&&pro->isVisible()&&!row->isLaneRow())
		{
			temp.push_back(pro);
		}

	}
	if (temp.size()>0)
	{
	prop=temp.at(rand()%temp.size());
	}
	else
		prop=nullptr;
	return prop;

}
//auto start_time = chrono::high_resolution_clock::now();
		//auto end_time = chrono::high_resolution_clock::now();
		//cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << endl;
//start_time=chrono::steady_clock::now();
	//			end_time=chrono::steady_clock::now();
