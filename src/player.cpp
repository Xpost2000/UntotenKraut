#include "player.h"
#include "world.h"

#include "texturemanager.h"

#include <iostream>

namespace game{
	Player::Player(float x, float y, float w, float h, float speed, float hp)
	: Entity(x,y,w,h), speed(speed), hp(hp), maxHp(hp){
		sprite.setW(w);
		sprite.setH(h);
		gunSprite.setW(w+10);
		gunSprite.setH(h+10);
		gunSprite.useOwnOrigin=false;
		gunSprite.rotateOriginOffsetX= w*0.5;
		gunSprite.rotateOriginOffsetY= h*0.5;
		gunSprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//M1911A1.png"));
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//dev_player_test.png"));

	}

	Player::Player(){
	}

	Player::~Player(){
	}

	void Player::fire(float mX, float mY, bool g){
		float angle = atan2( mY-y , mX-x );
//		sprite.setAngle(angle);
//		gunSprite.setAngle(angle);
		if(g){
			if(grenadeDelay<=0){
				bullets.push_back( Bullet(x, y, w/3, h/3, cos(angle)*7, sin(angle)*7, 50, 150, 135, true) );
				grenadeDelay=50;
			}
			return;
		}
		if( currentGun->canFire() ){
			if(currentGun->fire()){
				// currentGun->getExplosive()
				// check gun types to determine how to fire.
				if(currentGun->getExplosive()){
					bullets.push_back(Bullet(x, y, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage(), currentGun->getExplosiveRange(), true));
				}else{
					bullets.push_back(Bullet(x, y, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage()));
				}
				if(currentGun->getShotgun()){
					if(currentGun->getExplosive()){
						bullets.push_back(Bullet(x+3, y+5, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage(), currentGun->getExplosiveRange(), true));
						bullets.push_back(Bullet(x-3, y-5, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage(), currentGun->getExplosiveRange(), true));
	
					}else{
						bullets.push_back(Bullet(x+3, y+5, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage()));
						bullets.push_back(Bullet(x-3, y-5, w/4, h/4, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage()));
					}
				}
			}
		}
	}

	void Player::update( float dt, World& world ){
		if(hp < maxHp){
			hp+=dt*0.65;
		}
		if(grenadeDelay > 0){
			grenadeDelay--;
		}
		gunSprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//"+currentGun->getName()+".png"));
		sprite.setX(x);
		sprite.setY(y);
		gunSprite.setX(x);
		gunSprite.setY(y);
		currentGun->update(dt);
	}

	void Player::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite(sprite);
		renderer.drawSprite(gunSprite);
	}

	void Player::move( float dt, int direction, World& world, float speedModifier ){
		Player clone = *this; // why is this causing a side effect?
		const float speed=35;
		switch(direction){
			// up
			case 1:
				clone.y -= speed*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				for(auto &wall : world.getBarricades()){
					if(clone.touching(wall)){
						return;
					}
				}
				y -= speed*speedModifier*dt;
				break;
			// down
			case 2:
				clone.y += speed*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				for(auto &wall : world.getBarricades()){
					if(clone.touching(wall)){
						return;
					}
				}
				y += speed*speedModifier*dt;
				break;
			// left
			case 3:
				clone.x -= speed*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				for(auto &wall : world.getBarricades()){
					if(clone.touching(wall)){
						return;
					}
				}
				x -= speed*speedModifier*dt;
				break;
			// right
			case 4:
				clone.x += speed*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				for(auto &wall : world.getBarricades()){
					if(clone.touching(wall)){
						return;
					}
				}
				x += speed*speedModifier*dt;
				break;
		};
	}
};
