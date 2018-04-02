#include "gun.h"
#include "sound.h"

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
			core::audio::SoundManager::getInstance()->playSound(name+"_fire", 0);
			return true;
		}else{
			return false;
		}
       	}

	bool Gun::reload(float dt){
		if(magSize <= 0){ return false; }
		if(reloadSpeed > 0){
			reloadSpeed-=dt;
			return false;
		}else{
			magSize -= maxMagSize-currentMagSize;
			if(maxMagSize <= magSize){
				currentMagSize = maxMagSize;
			}else{
				currentMagSize = magSize;
			}
			reloadSpeed=reloadSpeedStart;
			currentMagSize = std::max(0, currentMagSize);
			magSize = std::max(0, magSize);
			return true;
		}
	}
};
