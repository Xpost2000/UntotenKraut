#ifndef WORLD_H
#define WORLD_H
#include "renderer.h"
#include "player.h"

#include "wall.h"
#include "zombie.h"
#include "bullet.h"

#include <vector>

namespace game{
	class Level;
	class World{
		public:
			World(){}
			~World(){}

			Player* getPlayer() { return player; }

			void loadLevel( Level& );

			void setPlayer(Player* nplayer) { player=nplayer;}

			void addWall(Wall& wall) { walls.push_back(wall); }
			void addWall(Wall wall) { walls.push_back(wall); }

			void addZombie(Zombie& zombie) { zombies.push_back(zombie); }
			void addZombie(Zombie zombie) { zombies.push_back(zombie); }

			std::vector<Wall>& getWalls() { return walls; }
			std::vector<Zombie>& getZombies() { return zombies; }

			void draw(core::gfx::Renderer&);
			void update(float dt);
		private:
			Player *player;
			std::vector<Wall> walls;
			std::vector<Zombie> zombies;
	};
};

#endif
