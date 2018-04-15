#include "bullet.h"
#include "world.h"

#include <iostream>

#include "texturemanager.h"

namespace game{
	Bullet::Bullet( float x, float y, float w, float h, float sX, float sY, float lifeTime, float damage ): Entity(x, y, w, h), speedX(sX), speedY(sY), lifeTime(lifeTime), damage(damage){
		sprite.setW(w);
		sprite.setH(h);
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_player_projectile.png"));
	}

	Bullet::~Bullet(){

	}

	void Bullet::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite( sprite );
	}

	void Bullet::update(float dt, World& world){
		for(auto& wall : world.getWalls()){
			if(touching(wall)){
				lifeTime=0;
				break;
			}
		}
		for(auto& zombie : world.getZombies()){
			if(touching(zombie)){
				zombie.setHp( zombie.getHp() - damage );
				zombie.bleed(speedX/6, speedY/6, dt);
				world.getScore() +=10;
				lifeTime=0;
				break;
			}
		}

		x += speedX;
		y += speedY;
		sprite.setX(x);
		sprite.setY(y);
		
		lifeTime-=dt;
	}
};
