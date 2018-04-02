#ifndef SPAWNER_H
#define SPAWNER_H

#include <vector>

/*
 * Other spawner type things are to be handled
 * by the game itself and not this class.
 *
 * It only populates a vector.
 */
namespace game{
	//TODO: Add trigger zone.
	template<class T>
	class Spawner{
		public:
			Spawner(std::vector<T>* ptr_to_vector, float spawn_delay, float x, float y, int maxSpawned=-1)
			: spawn_delay(0), spawn_delay_max(spawn_delay), x(x), y(y)
			{
				vectorPtr = ptr_to_vector;
			}
			void setCloneOf(T cloneOf){
				template_object = cloneOf;
				template_object.x = x;
				template_object.y = y;
			}
			void update(float dt){
				if(spawned < maxSpawned){
					if(spawn_delay <= 0){
						vectorPtr->push_back(template_object);
						spawned++;
						spawn_delay = spawn_delay_max;
					}
				}
				spawn_delay-=dt;
			}

			bool isActive() { return active; }
			void setActive(bool t) { active = t; }

			T& getClone() { return template_object; }

			void reset() { spawned=0; }
			void setMaxSpawned(int limit) { maxSpawned = limit; }

			float x, y;
			int getMax() { return maxSpawned; }
		private:
			int spawned=0, maxSpawned=0;
			T template_object;

			bool active=true;
			std::vector<T>* vectorPtr;
			float spawn_delay=0;
			float spawn_delay_max=0;
	};
};

#endif
