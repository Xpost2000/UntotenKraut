#ifndef BULLET_H
#define BULLET_H
#include "entity.h"
#include "sprite.h"

namespace game{
	class Bullet : public Entity{
		public:
			Bullet( float x, float y, float w, float h, float sX, float sY, float lifeTime, float damage, float explosionSize=0, bool explosive=false );
			Bullet();
			~Bullet();
			void draw(core::gfx::Renderer&);
			void update(float dt, World&);

			void setDamage( float dmg ) { damage = dmg; }
			float getDamage() { return damage; }

			void setSpeed(float x, float y){
				speedX= x;
				speedY= y;
			}

			float getSpeedX() { return speedX; }
			float getSpeedY() { return speedY; }
			bool isAlive() { return lifeTime > 0; }
			bool isExplosive() { return explosive;  }
			float getExplosionRange() { return explosionRange; }
		private:
			float explosionRange=0;
			bool explosive=false;
			bool exploding=false;
			float damage=0;
			float lifeTime=0;
			float speedX=0, speedY=0;
			core::gfx::Sprite sprite, explosionSprite;
	};
};

#endif
