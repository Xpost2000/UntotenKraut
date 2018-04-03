#include "world.h"
#include "texturemanager.h"

namespace game{
	Wall::Wall( float x, float y, float w, float h, core::gfx::Texture* tex, int gunCost)
	: Entity(x, y, w, h),
	hasGun(gunCost), weaponCost(gunCost){
		sprite = core::gfx::Sprite(x,y,w,h);
		sprite.setTexture(tex);
		gunTrigger = Entity(x-5,y-5,w+10,h+10);
	}

	void Wall::update(float dt, World& world){
	}

	void Wall::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite(sprite);
	}
};
