#ifndef WORLD_H
#define WORLD_H
#include "renderer.h"
#include "player.h"

#include "wall.h"
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

			std::vector<Wall>& getWalls() { return walls; }

			void draw(core::gfx::Renderer&);
			void update(float dt);
		private:
			Player *player;
			std::vector<Wall> walls;
	};
};

#endif
