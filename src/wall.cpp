#include "world.h"
#include "texturemanager.h"

namespace game{
	Wall::Wall( float x, float y, float w, float h, int gunCost)
	: Entity(x, y, w, h),
	hasGun(gunCost), weaponCost(gunCost){
		sprite = core::gfx::Sprite(x,y,w,h);
		gunTrigger = Entity(x-5,y-5,w+10,h+10);
		if(hasGun){
			sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_wallbuy_test.png"));
		}else{
			sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_wall_test.png"));
		}
	}

	void Wall::update(float dt, World& world){
	}

	void Wall::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite(sprite);
	}
};
