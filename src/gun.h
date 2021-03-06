#ifndef GAME_H
#define GAME_H
#include <string>
#include "bullet.h"
namespace game{
		/*
		 * It handles stats for bullet types that can
		 * be fired and a few other things
		 */
		class Gun{
			public:
				Gun();
				Gun( std::string name, float damage, float bulletSpeed, float bulletLifetime, float delay, bool shotgun, int maxAmmo, int magAmmo, float reloadSpeed, int cost=0, bool explosive=false, float explosiveRange=0 );
				// it will auto count down it's delay.
				void update(float dt);

				std::string getName() { return name; }

				float getDelay() { return delay; }
				
				bool canFire() { return delay <= 0; }
				bool getExplosive() { return explosive; }
				bool getShotgun() { return shotgun; }
				
				float getExplosiveRange() { return explosiveRange; }
				float getDamage(){ return damage; }
				float getBulletSpeed() { return bulletSpeed; }
				float getBulletLifetime() { return bulletSpeed; }

				int getCurrentCapacity() { return currentMagSize; }
				int getMaxCurrentCapacity() { return maxMagSize; }
				int getMaxCapacity(){ return magSize; }

				bool fire();
				bool reload(float dt);
				int gunCost=0;
			private:
				std::string name="Nothing";

				bool shotgun=false;
				float explosiveRange=0;
				bool explosive=false;

				int currentMagSize=0;
				int magSize=0;
				int maxMagSize=0;

				float damage=0;
				float bulletSpeed=0;
				float bulletLifetime=0;
				float delayStart=0;
				float delay=0;

				float reloadSpeed=0;
				float reloadSpeedStart=0;
		};
};
#endif
