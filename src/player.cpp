#include "player.h"
#include "world.h"

#include "texturemanager.h"

#include <iostream>

namespace game{
	Player::Player(float x, float y, float w, float h, float speed, float hp)
	: Entity(x,y,w,h), speed(speed), hp(hp){
		sprite.setW(w);
		sprite.setH(h);
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_player_test.png"));
	}

	Player::Player(){
	}

	Player::~Player(){
	}

	void Player::fire(float mX, float mY){
		float angle = atan2( mY -360 , mX -360 );
		if( currentGun->canFire() ){
			if(currentGun->fire()){
				bullets.push_back(Bullet(x, y, w/2, h/2, cos(angle)*currentGun->getBulletSpeed(), sin(angle)*currentGun->getBulletSpeed(), currentGun->getBulletLifetime(), currentGun->getDamage()));
			}
		}
	}

	void Player::update( float dt, World& world ){
		sprite.setX(x);
		sprite.setY(y);
		currentGun->update(dt);
	}

	void Player::draw(core::gfx::Renderer& renderer){
		//renderer.drawRect( x, y, w, h, 1, 0, 0, 1 );
		renderer.drawSprite(sprite);
	}

	void Player::move( float dt, int direction, World& world, float speedModifier ){
		Player clone = *this; // why is this causing a side effect?
		/*
		 * Wait I know why.....
		 * These crashes are what happens when I don't decouple rendering and game logic, logic.
		 */
		switch(direction){
			// up
			case 1:
				clone.y -= 20*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				y -= 20*speedModifier*dt;
				break;
			// down
			case 2:
				clone.y += 20*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				y += 20*speedModifier*dt;
				break;
			// left
			case 3:
				clone.x -= 20*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				x -= 20*speedModifier*dt;
				break;
			// right
			case 4:
				clone.x += 20*speedModifier*dt;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				x += 20*speedModifier*dt;
				break;
		};
	}
};
