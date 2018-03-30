#include "world.h"

namespace game{
	void World::draw(core::gfx::Renderer& renderer){
		for(auto& wall : walls){
			renderer.drawRect(wall.x, wall.y, wall.w, wall.h, 0.3, 0.3, 0.3, 1.0);
		}
	}

	void World::update(float dt){
	}
};
