#include "particlesystem.h"
#include "texturemanager.h"
#include "sprite.h"
#include <iostream>
#include <cstdlib>
namespace core{
	namespace gfx{
		ParticleSystem::ParticleSystem() : ParticleSystem(0, 0, 200){
		}
		ParticleSystem::ParticleSystem(float x, float y, int size) : size(size), x(x), y(y){
			std::cout << "Particle System of Size : " << size << std::endl;
			for(int i = 0 ; i < size; ++i){
				pool.push_back(Particle());
				Particle& p = pool[i];
				p.r=1;
				p.g=0;
				p.b=0;
				p.x=x;
				p.y=y;
				p.lifeTime=50;
			}
		}
		ParticleSystem::~ParticleSystem(){
		}
		void ParticleSystem::resetPositions(){
			for(int i = 0 ; i < size; ++i){
				Particle& p = pool[i];
				p.x=x+(rand()%15);
				p.y=y+(rand()%13);
			}
		}
		void ParticleSystem::update(float dt){
			if(active)
			for(int i = 0 ; i < size; ++i){
				Particle& p = pool[i];
				if(p.lifeTime>0){
				p.r=1;
				p.g=0;
				p.b=0;
				p.a=p.lifeTime/50;

				p.x+=speedX*cos(angle)-(rand()%6);
				p.y+=speedY*sin(angle)-(rand()%6);
				p.lifeTime--;
				}else{
					p.a=1;
					p.lifeTime=50;
					p.x=x;
					p.y=y;
				}
			}
		}
		void ParticleSystem::draw(Renderer& renderer){
			Sprite spr(0, 0, 15, 15);
			spr.setTexture(TextureManager::getInstance()->getTexture("assests\\textures\\particle_blob.png"));
			if(active)
			for(int i = 0; i < size; ++i){
				Particle& p = pool[i];
				spr.setX(p.x);
				spr.setY(p.y);
				if(p.lifeTime > 0){
				renderer.drawSprite(spr, p.r, p.g, p.b, p.a);
				}
			}
		}
		int ParticleSystem::getDeadParticle(){
			for(int i = 0; i < size; ++i){
				if(pool[i].lifeTime <= 0){
					return i;
				}
			}
			return 0; 
		}
		void ParticleSystem::setAttributes(float nSpeedX, float nSpeedY, float nAngle){
			speedX = nSpeedX;
			speedY = nSpeedY;
			angle = nAngle;
		}
	};
};
