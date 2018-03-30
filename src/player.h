#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "bullet.h"

#include "gun.h"

#include <vector>

namespace game{
	class Player : public Entity{
		public:
			Player( float x, float y, float w, float h, float speed, float hp );
			Player();
			~Player();

			void update(float dt, World&);
			void draw(core::gfx::Renderer& renderer);

			void setSpeed( float s ) { speed=s; }
			void setHp( float h ) { hp=h; }

			float getSpeed() { return speed; }
			float getHp() { return hp; }

			void fire(float mX, float mY);
			
			std::vector<Bullet>& getBullets() { return bullets; }

			void setGun(Gun g){ currentGun = g; }

			Gun &getGun() { return currentGun; }

			void move(int direction, World& world);
		private:
			core::gfx::Sprite sprite;
			Gun currentGun;

			std::vector<Bullet> bullets;

			bool fired=false;
			float speed=0;
			float hp=0;
	};
};
#endif
