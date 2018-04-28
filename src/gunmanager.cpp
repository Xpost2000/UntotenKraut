#include "gunmanager.h"
#include "texturemanager.h"
#include "sound.h"

namespace game{
	std::shared_ptr<GunManager> GunManager::instance;
	GunManager::GunManager(){

	}

	GunManager::~GunManager(){

	}

	void GunManager::addGun(std::string name, Gun gun){
		core::TextureManager::getInstance()->loadTexture("assests//ui//" + name + "_hud.png");
		core::TextureManager::getInstance()->loadTexture("assests//textures//"+name+".png");
		core::audio::SoundManager::getInstance()->addSound("assests//sounds//"+name+"_fire.wav", name+"_fire");	
		core::audio::SoundManager::getInstance()->addSound("assests//sounds//"+name+"_reload.wav", name+"_reload");	
		guns.insert(std::make_pair(name, gun));
		gunVecMap.push_back(std::make_pair(name, gun));
	}

	Gun GunManager::get(std::string name){
		if(guns.count(name))
			return guns[name];
	}
};
