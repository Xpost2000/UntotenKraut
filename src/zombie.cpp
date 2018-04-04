#include "zombie.h"
#include "math.h"
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
			if(notTested.empty()) break;
			current=notTested.front();
			current->visited=true;
			for(auto& n : current->neighbors){
				if(!n->visited && !n->block){
					notTested.push_back(n);
				}
				float possible = current->localValue + distance(current, n);
				if(possible < n->localValue){
					std::cout << "Setting parent" << std::endl;
					n->parent= current;
					n->localValue= possible;
					n->globalValue= n->localValue + distance(n, goal);
				}
			}
		}
		toFollow = goal;
		sprite.setX(x);
		sprite.setY(y);
		if(hp > 0){
			float targetX=0;
			float targetY=0;

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
		toFollow=goal;
		renderer.drawRect( toFollow->x*35, toFollow->y*35, 35, 35 );
		renderer.drawRect( start->x*35, start->y*35, 35, 35 );
		while(toFollow->parent != nullptr){
			renderer.drawRect( toFollow->x*35, toFollow->y*35, 35, 35 );
			toFollow=toFollow->parent;
		}
	
	}
};
