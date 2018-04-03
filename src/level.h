#ifndef LEVEL_H
#define LEVEL_H
#include "zombie.h"
#include "spawner.h"
#include "barricade.h"
#include "detail_ent.h"
#include "wall.h"

#include <vector>
namespace game{
	class Level{
		public:
			Level(){}
			~Level(){}
		private:
			friend class World;
			friend class LevelLoader;
			float pX=0, pY=0;
			std::vector<DetailEntity> detail_ents;
			std::vector<Wall> walls;
			std::vector<Barricade> barricades;
			std::vector<Spawner<Zombie>> zombieSpawners;
	};
};
#endif
