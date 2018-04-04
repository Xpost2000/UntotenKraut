#include "zombie.h"
#include "world.h"
#include <algorithm>
#include <iostream>

#include "texturemanager.h"
namespace game{
	Zombie::Zombie(float x, float y, float w, float h, float speed, float hp) : Entity(x, y, w, h), speed(speed), hp(hp){
		sprite.setW(w); 
		sprite.setH(h); 
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_zombie_test.png"));	
	}
	Zombie::Zombie(){

	}
	Zombie::~Zombie(){

	}

	void Zombie::update(float dt, World& world){
		sprite.setX(x);
		sprite.setY(y);
		if(hp > 0){
			//float targetX=world.getPlayer()->x, targetY=world.getPlayer()->y;
			float targetX=0;
			float targetY=0;
				
			std::vector<Barricade> &barricades = world.getBarricades();
			// I hope this is done correctly...
			std::sort(barricades.begin(), barricades.end(), [&](Barricade& a, Barricade& b)->bool{
				if((a.x - x)<(b.x - x) && (a.y - y)<(b.y - y)){
					if(a.getHealth()){
						std::cout << "A is closest" << std::endl;
						return true;
					}else{
						std::cout << "B is closest because A is dead." << std::endl;
						return false;
					}
				}else{
					return false;
				}
			});
			float dist = sqrt( pow(barricades.begin()->x-x,2)+pow(barricades.begin()->y-y,2) );
			float dist1 = sqrt( pow(world.getPlayer()->x-x,2)+pow(world.getPlayer()->y-y,2) );
			/*
			This is much more buggier.
			if( dist < dist1 ){
				if(barricades.begin()->getHealth()){
					targetX = barricades.begin()->x;
					targetY = barricades.begin()->y;
				}else{
					targetX = world.getPlayer()->x;
					targetY = world.getPlayer()->y;
				}
			}else{*/
				targetX = world.getPlayer()->x;
				targetY = world.getPlayer()->y;
			//}
			float angle = atan2(targetY - y, targetX - x); // TRIGONOMIC MAGIC THAT SAYS TO FOLLOW THE PLAYER BY BASICALLY A STRAIGHT LINE.
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
		for(auto &barricade : world.getBarricades()){
			if(clone.touching(barricade) && barricade.getHealth()>0){
				if(hitDelay <= 0){
					barricade.setHealth(barricade.getHealth()-25);	
					hitDelay=15;
				}
				return; 
				break;
			}
		}
		for(auto &wall : world.getWalls()){
			if(clone.touching(wall)){
				return;
				break;
			}
		}
		for(auto& zombie : world.getZombies()){
			if(clone.touching(zombie) & &zombie != this){
				return;
				break;
			}
		}
		x += speed* cos(angle)*dt;
		y += speed* sin(angle)*dt;
	}

	void Zombie::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite( sprite );
	}
};
