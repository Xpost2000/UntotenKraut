#include "bullet.h"
#include "world.h"
#include "sound.h"
#include "texturemanager.h"

#include <iostream>


namespace game{
	Bullet::Bullet( float x, float y, float w, float h, float sX, float sY, float lifeTime, float damage, float explosionSize, bool explosive ): Entity(x, y, w, h), speedX(sX), speedY(sY), lifeTime(lifeTime), damage(damage), explosionRange(explosionSize), explosive(explosive){
		sprite.setW(w);
		sprite.setH(h);
		explosionSprite.setW(explosionRange);
		explosionSprite.setH(explosionRange);
		explosionSprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//explosion.png"));
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//dev_player_projectile.png"));
		exploding=false;
	}

	Bullet::~Bullet(){

	}

	void Bullet::draw(core::gfx::Renderer& renderer){
		if(lifeTime<=25)
		renderer.drawSprite( explosionSprite, 1, 1, 1, lifeTime/25 );
		renderer.drawSprite( sprite );
	}

	void Bullet::update(float dt, World& world){
		for(auto& wall : world.getWalls()){
			if(touching(wall)){
				if(!explosive){
					core::audio::SoundManager::getInstance()->playSound("hit", 3);
					lifeTime=0;
				}else{
					if(!exploding){
						lifeTime = 23;	
					}
					exploding=true;
				}
				break;
			}
		}
		Entity explosion(x-explosionRange/2, y-explosionRange/2, explosionRange, explosionRange);
		for(auto& zombie : world.getZombies()){
			if(explosive ? (explosion.touching(zombie)||touching(zombie)) && zombie.getHp()>0 && lifeTime>=22 : touching(zombie) && zombie.getHp()>0){
				if(explosive){
					zombie.setHp( zombie.getHp() - damage );
					zombie.bleed(speedX/6, speedY/6, dt);
					world.getScore() +=10;
				}else{
					zombie.setHp( zombie.getHp() - damage );
					zombie.bleed(speedX/6, speedY/6, dt);
					world.getScore() +=10;
				}
				if(explosive){
					if(!exploding)
						lifeTime=23;
					exploding=true;
				}else{
					lifeTime=0;
				}
			}
		}
		if(exploding){
			if(explosion.touching(*world.getPlayer())&& lifeTime >= 22){
				// won't kill ya instantly. But it's going to hurt.
				world.getPlayer()->setHp(world.getPlayer()->getHp()-damage*0.55);
				lifeTime=21;
				core::audio::SoundManager::getInstance()->playSound("explosion", -1);
			}
		}
		if(lifeTime <= 23 && lifeTime >= 22 && explosive){
			core::audio::SoundManager::getInstance()->playSound("explosion", -1);
		}

		if(!explosive){
			x += speedX;
			y += speedY;
		}else{
			if(lifeTime > 25){
				x += speedX;
				y += speedY;
			}
		}
		explosionSprite.setX(x-explosionRange/2);
		explosionSprite.setY(y-explosionRange/2);
		sprite.setX(x);
		sprite.setY(y);
		
		lifeTime-=dt;
	}
};
