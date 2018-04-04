#include "zombie.h"
#include <list>
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
			float targetX=0;
			float targetY=0;
			targetX = world.getPlayer()->x;
			targetY = world.getPlayer()->y;

			std::vector<Barricade> &barricades = world.getBarricades();
			auto distance =[&](Entity *x, Entity *y){
				return sqrt((x->x-y->x)*(x->x-y->x)+(x->y-y->y)*(x->y-y->y));
			};
			auto byDistance = [&](Barricade& x, Barricade& y){
				float distX=sqrt((x.x-targetX)*(x.x-targetX)+(x.y-targetY)*(x.y-targetY));
				float distY=sqrt((y.x-targetX)*(y.x-targetX)+(y.y-targetY)*(y.y-targetY));
				return distX < distY;
			};
			std::sort(barricades.begin(), barricades.end(), byDistance);
			targetX = barricades.front().x;
			targetY = barricades.front().y;
			if(distance(this, &barricades.front()) > distance(this, world.getPlayer())){
				targetX = world.getPlayer()->x;
				targetY = world.getPlayer()->y;
			}

			float angle = atan2(targetY - y, targetX - x); 
			

			if(touching(*world.getPlayer())&& hitDelay<=0){
				world.getPlayer()->setHp( world.getPlayer()->getHp() - 50 );
				hitDelay=13;
			}

			hitDelay-=dt;
			moveAngle(angle, world, dt);
		}
	}

		void Zombie::moveAngle(float angle, World& world, float dt){
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

			x += speed* cos(angle)*dt;
			y += speed* sin(angle)*dt;
		}

		void Zombie::moveDirection(int direction, World& world, float dt){
			int speedModifier=1;
			Zombie clone= *this;
			switch(direction){
				// up
				case 1:
					clone.y -= speed*speedModifier*dt;
					for(auto &wall : world.getWalls()){
						if(clone.touching(wall)){
							return;
						}
					}
					y -= speed*dt;
					break;
				// down
				case 2:
					clone.y += speed*speedModifier*dt;
					for(auto &wall : world.getWalls()){
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
				x += speed*speedModifier*dt;
				break;
		};

	}

	void Zombie::draw(core::gfx::Renderer& renderer){
		renderer.drawSprite( sprite );
	}
};
