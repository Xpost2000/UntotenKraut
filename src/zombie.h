#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "entity.h"
#include "sprite.h"
#include "particlesystem.h"
#include "pathfindingnode.h"
namespace game{
	class Zombie : public Entity{
		public:
			Zombie( float x, float y, float w, float h, float speed, float hp );
			Zombie();
			~Zombie();
			void update(float dt, World&);
			void draw(core::gfx::Renderer&);

			void setHp( float nhp ) { hp = nhp; }
			float getHp() { return hp; }

			void setSpeed( float nspeed ) { speed = nspeed; }
			float getSpeed() { return speed; }

			void bleed(float sX, float sY, float dt){ps.speedX = sX; ps.speedY = sY; ps.active=true; bloodTimer=50; ps.x = x; ps.y = y; ps.resetPositions(); ps.update(dt);}
			bool doneBleeding() { return bloodTimer<=0; }

			// zombies can't strafe. they move from an angle.
			bool cleared=false;
		private:
			float bloodTimer=60;
			std::vector<Node> gridWorld;
			Node* current=nullptr;
			Node* goal=nullptr;
			Node* start=nullptr;

			Node* toFollow=nullptr;
			core::gfx::Sprite sprite;
			core::gfx::ParticleSystem ps;
			void moveAngle(float angle, World& world, float dt);
			bool moveToPoint(int x, int y, World& world, float dt);
			void moveDirection(int direction, World& world, float dt);
			float hitDelay=0;
			float speed=0, hp=0;
	};
};
#endif
