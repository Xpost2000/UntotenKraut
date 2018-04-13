#ifndef WALL_H
#define WALL_H

#include "entity.h"
#include "sprite.h"
#include "gunmanager.h"
#include "gun.h"

namespace game{
	class Wall : public Entity{
		public:
			Wall( float x, float y, float w, float h, core::gfx::Texture* tex, int gunCost=0 );
			Wall( float x, float y, float w, float h, core::gfx::Texture* tex, Gun gun );
			void update(float dt, World&);
			void draw(core::gfx::Renderer&);
			int getType() { return type; }

			int getCost() { return weaponCost; }
			bool getHasGun() { return hasGun; }
			Gun getWallWeapon() { return wallWeapon; }
			Entity &getTrigger() { return gunTrigger; }
		private:	
			friend class LevelLoader;
			friend class World;
			bool hasGun=false;
			int  weaponCost=0;
			Gun wallWeapon;

			Entity gunTrigger;

			core::gfx::Sprite sprite;
			int type=0;
	};
};

#endif
