#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "entity.h"
#include "sprite.h"
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

			// zombies can't strafe. they move from an angle.
		private:
			Node* gridWorld=nullptr;
			Node* current=nullptr;
			Node* goal=nullptr;
			Node* start=nullptr;

			Node* toFollow=nullptr;
			core::gfx::Sprite sprite;
			void moveAngle(float angle, World& world, float dt);
			void moveDirection(int direction, World& world, float dt);
			float hitDelay=0;
			float speed=0, hp=0;
			bool brokenBarricade=false;
	};
};
#endif
