#include "bullet.h"
#include "world.h"

namespace game{
	Bullet::Bullet( float x, float y, float w, float h, float sX, float sY, float lifeTime, float damage ): Entity(x, y, w, h), speedX(sX), speedY(sY), lifeTime(lifeTime), damage(damage){
		sprite.setW(w);
		sprite.setW(h);
		sprite.loadTexture("assests\\textures\\dev_player_projectile.png");
	}

	Bullet::~Bullet(){

	}

	void Bullet::draw(core::gfx::Renderer& renderer){
		renderer.drawRect( x, y, w, h, 1, 0, 1, 1 );
	}

	void Bullet::update(float dt, World& world){
		sprite.setX(x);
		sprite.setY(y);

		for(auto& wall : world.getWalls()){
			if(touching(wall)){
				lifeTime=0;
			}
		}

		x += speedX;
		y += speedY;
		
		lifeTime-=dt;
	}
};
