#ifndef WORLD_H
#define WORLD_H
#include "renderer.h"
#include "player.h"

#include "wall.h"
#include "barricade.h"
#include "zombie.h"
#include "bullet.h"
#include "detail_ent.h"

#include "spawner.h"

#include <vector>
#include "level.h"

namespace game{
	// actually it's more like gamestate.
	// The world contains everything including game logic stuff
	// (because I don't have messaging systems to deliever signals
	// and stuff.)
	class World{
		public:
			World(){ zombies.reserve(32); }
			~World(){}

			Player* getPlayer() { return player; }

			void loadLevel( Level lvl ){
				barricades = lvl.barricades;
				walls = lvl.walls;
				zombieSpawners = lvl.zombieSpawners;
				detail_ents = lvl.detail_ents;
				for(auto& s : zombieSpawners){
					s.setVectorPtr(&zombies);
					s.setCloneOf(Zombie(0, 0, 32, 32, 5, 50));
				}
				player->x=lvl.pX;
				player->y=lvl.pY;
				w = lvl.w;
				h = lvl.h;
			}

			void setPlayer(Player* nplayer) { player=nplayer;}

			void addDetail(DetailEntity de) { detail_ents.push_back(de); }
			void addDetail(DetailEntity &de) { detail_ents.push_back(de); }
			void addWall(Wall& wall) { walls.push_back(wall); }
			void addWall(Wall wall) { walls.push_back(wall); }
			void addBarricade(Barricade& bar) { barricades.push_back(bar); }
			void addBarricade(Barricade bar) { barricades.push_back(bar); }

			void addZombie(Zombie& zombie) { zombies.push_back(zombie); }
			void addZombie(Zombie zombie) { zombies.push_back(zombie); }
			void addSpawner(float x, float y, float delay, int limit=-1){ 
				zombieSpawners.push_back(Spawner<Zombie>(&zombies, delay, x, y, limit));
				zombieSpawners.back().setCloneOf(Zombie(0, 0, 30, 30, 5, 50));
		       	}

			void reinitSpawners(){
				for(auto &s : zombieSpawners){
					s.setVectorPtr(&zombies);
					s.setCloneOf(Zombie(0, 0, 30, 30, 5, 50));
				}
				zombieSpawnHp=50;
			}

			std::vector<Wall>& getWalls() { return walls; }
			std::vector<DetailEntity>& getDetailEntities() { return detail_ents; }
			std::vector<Zombie>& getZombies() { return zombies; }
			std::vector<Spawner<Zombie>>& getSpawner() { return zombieSpawners; }
			std::vector<Barricade>& getBarricades() { return barricades; }

			void draw(core::gfx::Renderer&);
			void update(float dt);

			void nextWave() { 
				if(grenadeCount <= 4){
					grenadeCount+=2;
				}
				int sum=0;
				zombies.clear();
				zombieSpawnHp+=16;
				for(auto& spawner : zombieSpawners){
					spawner.getClone().setHp(zombieSpawnHp);
					sum+=spawner.getMax()+1;
				}
				// so the game doesn't crap itself.
				if(sum <= 24){
				for(auto& spawner : zombieSpawners){
					spawner.reset();
					spawner.setMaxSpawned(spawner.getMax()+1);
				}
				}else{
				for(auto& spawner : zombieSpawners){
					spawner.reset();
					spawner.setMaxSpawned(spawner.getMax());
				}
				}
				
		        }

			unsigned int &getScore(){ return score; }
			unsigned int &getKillCount(){ return killCount; }
			int getMaxZombies(){
				int sum=0;
				for(auto spawner : zombieSpawners){
					sum += spawner.getMax();
				}
				return sum;
			}
			int& getWidth(){ return w; }
			int& getHeight() { return h; }
			int& getGrenadeCount() { return grenadeCount; }
		private:
			float zombieSpawnHp=50;
			int w=0,h=0;
			int grenadeCount=0;
			Player *player;
			std::vector<Wall> walls;
			std::vector<Barricade> barricades;
			std::vector<Zombie> zombies;
			std::vector<DetailEntity> detail_ents;

			std::vector<Spawner<Zombie>> zombieSpawners;

			unsigned int score=200,killCount=0;
	};
};

#endif
