#include "world.h"

namespace game{
	Wall::Wall( float x, float y, float w, float h )
	: Entity(x, y, w, h){
	}

	void Wall::update(float dt, World& world){
	}

	void Wall::draw(core::gfx::Renderer& renderer){
		renderer.drawRect(x, y, w, h, 0.3, 0.3, 0.3, 1);
	}
};
