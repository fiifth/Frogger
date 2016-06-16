/*
 * Projectile.h
 *
 *  Created on: 4-apr.-2016
 *      Author: Kwinten
 */

#ifndef ABSTRACT_ENTITIES_PROJECTILE_H_
#define ABSTRACT_ENTITIES_PROJECTILE_H_
#include "Abstract/Entities/Props.h"
#include "Abstract/Entity.h"
#include "Abstract/Entities/Player.h"
namespace frogger
{
	class Projectile: public frogger::Props
	{
		public:
			Projectile();
			virtual ~Projectile();
			bool itemListEmpty();
			void collision(Player* player);
			void initProjectile(int speedR ,int dividerR ,char directionR,int h,int yR,int x);
	};
}

#endif /* ABSTRACT_ENTITIES_PROJECTILE_H_ */
