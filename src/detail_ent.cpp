#include "detail_ent.h"

namespace game{
	DetailEntity::DetailEntity(float x, float y, float w, float h, core::gfx::Texture* tex):
	Entity(x,y,w,h){
		spr = core::gfx::Sprite(x,y,w,h);
		spr.setTexture(tex);
	}

	DetailEntity::~DetailEntity(){
	}

	void DetailEntity::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite(spr, 0.8, 0.8, 0.8);
	}
};
