#include "gun.h"
#include <iostream>

namespace game{
	Gun::Gun(){}
	Gun::Gun( std::string name, float damage, float bulletSpeed, float bulletLifetime, float delay, bool fullAuto, int maxAmmo, int magAmmo, float reloadSpeed )
	: name(name), fullAuto(fullAuto), damage(damage), bulletSpeed(bulletSpeed), bulletLifetime(bulletLifetime), delayStart(delay), currentMagSize(magAmmo), magSize(maxAmmo), reloadSpeed(reloadSpeed), reloadSpeedStart(reloadSpeed){
		maxMagSize = magAmmo;
	}

	void Gun::update(float dt){
		if(!canFire()){
			delay-=dt;
		}
		if(currentMagSize<=0){
			reload(dt);
		}
	}

	bool Gun::fire(){ 
		if(currentMagSize > 0){
			delay = delayStart;
			currentMagSize--;
			return true;
		}else{
			return false;
		}
       	}

	bool Gun::reload(float dt){
		if(reloadSpeed > 0){
			std::cout << "RELOAD SPEED: " << reloadSpeed << std::endl;
			reloadSpeed-=dt;
			return false;
		}else{
			magSize -= maxMagSize-currentMagSize;
			currentMagSize = maxMagSize;
			reloadSpeed=reloadSpeedStart;
			return true;
		}
	}
};
