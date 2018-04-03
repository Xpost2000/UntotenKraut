#include "world.h"
#include "texturemanager.h"

namespace game{
	Wall::Wall( float x, float y, float w, float h )
	: Entity(x, y, w, h){
		sprite = core::gfx::Sprite(x,y,w,h);
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_wall_test.png"));
	}

	void Wall::update(float dt, World& world){
	}

	void Wall::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite(sprite);
	}
};
