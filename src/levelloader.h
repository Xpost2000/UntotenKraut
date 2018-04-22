#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include <fstream>
#include <map>

#include <string>

#include "level.h"

namespace game{
	class LevelLoader{
		public:
			void load(std::string file, std::string levelName);
			void loadNew(std::string file, std::string levelName);
			Level getLevel(std::string name) { 
				if(levels.count(name))
				return levels[name]; 
				else
				return Level();
			}
		private:
			std::map<std::string, Level> levels;
	};
};

#endif
