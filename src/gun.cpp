#include "gun.h"

namespace game{
	Gun::Gun(){}
	Gun::Gun( std::string name, float damage, float bulletSpeed, float bulletLifetime, float delay, bool fullAuto )
	: name(name), fullAuto(fullAuto), damage(damage), bulletSpeed(bulletSpeed), bulletLifetime(bulletLifetime), delayStart(delay){
	}

	void Gun::update(float dt){
		if(!canFire()){
			delay-=dt;
		}
	}
};
