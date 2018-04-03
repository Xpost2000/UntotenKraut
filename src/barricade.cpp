#include "barricade.h"
#include "texturemanager.h"

namespace game{
	Barricade::Barricade(float x, float y, float w, float h)
	: Entity(x, y, w, h){
		sprites[0] = core::gfx::Sprite(x,y,w,h);
		sprites[1] = core::gfx::Sprite(x,y,w,h);
		sprites[0].setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_barricade_test.png"));
		sprites[1].setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_512_tset.png"));
	}

	void Barricade::draw(core::gfx::Renderer& renderer){
		if(health <= 0){
			renderer.drawSprite(sprites[1]);
		}else{
			renderer.drawSprite(sprites[0]);
		}
	}
};
