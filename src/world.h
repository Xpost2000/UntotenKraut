#ifndef WORLD_H
#define WORLD_H
#include "renderer.h"
#include "player.h"

#include "wall.h"
#include "zombie.h"
#include "bullet.h"

#include "spawner.h"

#include <vector>

namespace game{
	// actually it's more like gamestate.
	// The world contains everything including game logic stuff
	// (because I don't have messaging systems to deliever signals
	// and stuff.)
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
			void addSpawner(float x, float y, float delay){ 
				zombieSpawners.push_back(Spawner<Zombie>(&zombies, delay, x, y));
				zombieSpawners.back().setCloneOf(Zombie(0, 0, 30, 30, 10, 50));
		       	}

			std::vector<Wall>& getWalls() { return walls; }
			std::vector<Zombie>& getZombies() { return zombies; }

			void draw(core::gfx::Renderer&);
			void update(float dt);

			int &getScore(){ return score; }
			int &getKillcount(){ return killCount; }
		private:
			Player *player;
			std::vector<Wall> walls;
			std::vector<Zombie> zombies;

			std::vector<Spawner<Zombie>> zombieSpawners;

			int score=0,killCount=0;
	};
};

#endif
