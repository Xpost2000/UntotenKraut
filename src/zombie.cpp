#include "zombie.h"
#include "sound.h"

#include "math.h"
#include "world.h"

#include <list>
#include <algorithm>
#include <iostream>

#include "texturemanager.h"
namespace game{
	Zombie::Zombie(float x, float y, float w, float h, float speed, float hp) : Entity(x, y, w, h), speed(speed), hp(hp){
		sprite.setW(w); 
		sprite.setH(h); 
		sprite.setTexture(core::TextureManager::getInstance()->getTexture("assests//textures//dev_zombie_test.png"));	
	}
	Zombie::Zombie(){

	}
	Zombie::~Zombie(){
		if(gridWorld) { delete gridWorld; gridWorld=nullptr; }
	}

	void Zombie::update(float dt, World& world){
		if(gridWorld==nullptr){
			gridWorld = new Node[world.getWidth()*world.getHeight()];	
			for(int y = 0; y < world.getHeight(); ++y){
				for(int x = 0; x < world.getWidth(); ++x){
					gridWorld[y*world.getWidth()+x]= Node(x,y);
				}
			}	
			for(int y = 0; y < world.getHeight(); ++y){
				for(int x = 0; x < world.getWidth(); ++x){
					if(y>0){
						gridWorld[y*world.getWidth()+x].neighbors.push_back(&gridWorld[(y-1)*world.getWidth()+(x+0)]);
					}
					if(y<world.getHeight()-1){
						gridWorld[y*world.getWidth()+x].neighbors.push_back(&gridWorld[(y+1)*world.getWidth()+(x+0)]);
					}
					if(x>0){
						gridWorld[y*world.getWidth()+x].neighbors.push_back(&gridWorld[(y+0)*world.getWidth()+(x-1)]);
					}
					if(x<world.getWidth()-1){
						gridWorld[y*world.getWidth()+x].neighbors.push_back(&gridWorld[(y+0)*world.getWidth()+(x+1)]);
					}
				}
			}
			int gridX=x/35;
			int gridY=y/35;
			int pXGrid=world.getPlayer()->x/35;
			int pYGrid=world.getPlayer()->y/35;
			start = &gridWorld[gridY*world.getWidth()+gridX]; 
			goal = &gridWorld[pYGrid*world.getWidth()+pXGrid]; 
			for(auto &wall : world.getWalls()){
				int gridX = wall.x/35;
				int gridY = wall.y/35;
				gridWorld[gridY*world.getWidth()+gridX].block=true;
			}
		}
		auto distance = [](Node* a, Node* b){
			return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		};
		for(int y = 0; y < world.getHeight(); ++y){
			for(int x = 0; x < world.getWidth(); ++x){
				gridWorld[y*world.getWidth()+x].visited=false;
				gridWorld[y*world.getWidth()+x].globalValue=INFINITY;
				gridWorld[y*world.getWidth()+x].localValue=INFINITY;
				gridWorld[y*world.getWidth()+x].parent=nullptr;
			}
		}	
		int gridX=x/35;
		int gridY=y/35;
		int pXGrid=world.getPlayer()->x/35;
		int pYGrid=world.getPlayer()->y/35;
		start = &gridWorld[gridY*world.getWidth()+gridX]; 
		goal = &gridWorld[pYGrid*world.getWidth()+pXGrid]; 
		current = start;
		start->localValue=0;
		start->globalValue=distance(start, goal);
		std::list<Node*> notTested;
		notTested.push_back(start);
		while(!notTested.empty() && current != goal){
			notTested.sort([](const Node* lhs, const Node* rhs){ return lhs->globalValue < rhs->globalValue; });
			while(!notTested.empty() && notTested.front()->visited){
				notTested.pop_front();
			}
			current=notTested.front();
			current->visited=true;
			for(auto& n : current->neighbors){
				if(!n->visited && !n->block){
					notTested.push_back(n);
				}
				float possible = current->localValue + distance(current, n);
				if(possible < n->localValue){
					n->parent= current;
					n->localValue= possible;
					n->globalValue= n->localValue + distance(n, goal);
				}
			}
		}
		std::list<Node*> path;
		toFollow=goal;
		while(toFollow->parent != nullptr){
			path.push_back(toFollow);
			toFollow = toFollow->parent;
		}
		path.reverse();
		if(hp > 0){
			float targetX=0;
			float targetY=0;

			float angle = atan2(targetY - y, targetX - x); 

			if(path.front() != goal && path.front() != nullptr){
				if(moveToPoint(path.front()->x*35, path.front()->y*35, world, dt)){
					path.pop_front();
				}
			}else if(path.front() == goal){
				moveToPoint(world.getPlayer()->x, world.getPlayer()->y, world, dt);
			}
			
			if(touching(*world.getPlayer())&& hitDelay<=0){
				world.getPlayer()->setHp( world.getPlayer()->getHp() - 14 );

				core::audio::SoundManager::getInstance()->playSound("hurt", 5);
				hitDelay=13;
			}

			hitDelay-=dt;
		}
		sprite.setX(x);
		sprite.setY(y);
		ps.update(dt);
		if(bloodTimer <= 0){
			ps.active=false;
		}else{
			bloodTimer--;
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
					for(auto &z : world.getZombies()){
						if(clone.touching(z) && &z != this){ return; break; }
					}
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
					for(auto &z : world.getZombies()){
						if(clone.touching(z) && &z != this){ return; break; }
					}
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
					for(auto &z : world.getZombies()){
						if(clone.touching(z) && &z != this){ return; break; }
					}
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
					for(auto &z : world.getZombies()){
						if(clone.touching(z) && &z != this){ return; break; }
					}
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
					x += speed*speedModifier*dt;
				break;
		};

	}

	void Zombie::draw(core::gfx::Renderer& renderer){
		if(hp>0)
		renderer.drawSprite( sprite );	
		if(ps.active)
		ps.draw(renderer);
	}

	bool Zombie::moveToPoint(int tx, int ty, World& world, float dt){
		if(x!=tx || y!=ty){
			if( tx > x ){
				moveDirection(4, world, dt);
			}
			if( tx < x ){
				moveDirection(3, world, dt);
			}
			if( ty > y ){
				moveDirection(2, world, dt);
			}
			if( ty < y ){
				moveDirection(1, world, dt);
			}
			return false;
		}
		return true;
	}
};
