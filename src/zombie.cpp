#include "zombie.h"
#include "world.h"
#include <algorithm>
namespace game{
	Zombie::Zombie(float x, float y, float w, float h, float speed, float hp) : Entity(x, y, w, h), speed(speed), hp(hp){
	}
	Zombie::Zombie(){

	}
	Zombie::~Zombie(){

	}

	void Zombie::update(float dt, World& world){
		if(hp > 0){
			float targetX=world.getPlayer()->x, targetY=world.getPlayer()->y;
			float angle = atan2(targetY - y, targetX - x);

			if(touching(*world.getPlayer())&& hitDelay<=0){
				world.getPlayer()->setHp( world.getPlayer()->getHp() - 50 );
				hitDelay=13;
			}

			// now because there are no other objects to
			// compare distances of. Just target the player.

			hitDelay-=dt;
			move(angle, world, dt);
		}
	}

	void Zombie::move(float angle, World& world, float dt){
		Zombie clone= *this;
		clone.x += speed* cos(angle)*dt;
		clone.y += speed* sin(angle)*dt;
		for(auto wall : world.getWalls()){
			if(clone.touching(wall)){
				return;
				break;
			}
		}
		x += speed* cos(angle)*dt;
		y += speed* sin(angle)*dt;
	}

	void Zombie::draw(core::gfx::Renderer& renderer){
		renderer.drawRect(x, y, w, h, 0, 1, 0, 1);
	}
};
