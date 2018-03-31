#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "entity.h"
namespace game{
	class Zombie : public Entity{
		public:
			Zombie( float x, float y, float w, float h, float speed, float hp );
			Zombie();
			~Zombie();
			void update(float dt, World&);
			void draw(core::gfx::Renderer&);

			void setHp( float nhp ) { hp = nhp; }
			float getHp() { return hp; }

			void setSpeed( float nspeed ) { speed = nspeed; }
			float getSpeed() { return speed; }
		private:
			float hitDelay=0;
			float speed=0, hp=0;
	};
};
#endif
