#include "player.h"
#include "world.h"

namespace game{
	Player::Player(float x, float y, float w, float h, float speed, float hp)
	: Entity(x,y,w,h), speed(speed), hp(hp){
		sprite.setW(w);
		sprite.setH(h);
		sprite.loadTexture("assests\\textures\\dev_player_test.png");
	}

	Player::Player(){
	}

	Player::~Player(){
	}

	void Player::fire(float mX, float mY){
		float angle = atan2( mY - y, mX - x );
		if( currentGun.canFire() ){
			currentGun.fire();
			bullets.push_back(Bullet(x, y, w/2, h/2, cos(angle)*currentGun.getBulletSpeed(), sin(angle)*currentGun.getBulletSpeed(), currentGun.getBulletLifetime(), currentGun.getDamage()));
		}
	}

	void Player::update( float dt, World& world ){
		sprite.setX(x);
		sprite.setY(y);
		currentGun.update(dt);
	}

	void Player::draw(core::gfx::Renderer& renderer){
		renderer.drawRect( x, y, w, h, 1, 0, 0, 1 );
	}

	void Player::move( int direction, World& world ){
		Player clone = *this;
		switch(direction){
			// up
			case 1:
				clone.y -= 4;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				y -= 4;
				break;
			// down
			case 2:
				clone.y += 4;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				y += 4;
				break;
			// left
			case 3:
				clone.x -= 4;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				x -= 4;
				break;
			// right
			case 4:
				clone.x += 4;
				for(auto &wall : world.getWalls()){
					if(clone.touching(wall)){
						return;
					}
				}
				x += 4;
				break;
		};
	}
};
