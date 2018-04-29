#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "bullet.h"

#include "gun.h"
#include "input.h"

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
			void setMaxHp( float h ) { maxHp=h; }

			float getSpeed() { return speed; }
			float getHp() { return hp; }
			float getMaxHp() { return maxHp; }

			void fire(float mX, float mY, bool g=false);
			
			std::vector<Bullet>& getBullets() { return bullets; }

			void setGuns(Gun gun1, Gun gun2){ guns[0]=gun1; guns[1]=gun2; }
			// TODO: have checking.
			void useGun(int index){
				if(guns[index].getName() == "Nothing"){
					return;
				}else{
					currentGun = &guns[index];
				}
			}

			Gun &getGun() { return *currentGun; }
			Gun* getGuns() { return guns; }

			void move(float dt, int direction, World& world, float speedModifier=1);
			float getGrenadeDelay(){ return grenadeDelay; }
			void setAngle(float angle){
				sprite.setAngle(angle);
				gunSprite.setAngle(angle);
			}
		private:
			core::gfx::Sprite sprite, gunSprite;
			Gun  guns[2];
			Gun* currentGun;

			std::vector<Bullet> bullets;

			bool fired=false;
			float speed=0;
			float hp=0;
			float maxHp=0;
			float grenadeDelay=0;
	};
};
#endif
