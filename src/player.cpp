#include "player.h"

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
		bullets.push_back(Bullet(x, y, w/2, h/2, cos(angle), sin(angle), 100, 30));
	}

	void Player::update( float dt ){
		sprite.setX(x);
		sprite.setY(y);
	}

	void Player::draw(core::gfx::Renderer& renderer){
		renderer.drawRect( x, y, w, h, 1, 0, 0, 1 );
	}
};
