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

			// now because there are no other objects to
			// compare distances of. Just target the player.

			x += speed* cos(angle)*dt;
			y += speed* sin(angle)*dt;
		}
	}

	void Zombie::draw(core::gfx::Renderer& renderer){
		renderer.drawRect(x, y, w, h, 0, 1, 0, 1);
	}
};
