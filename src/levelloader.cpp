#include "levelloader.h"
namespace game{
	//size is 30
	void LevelLoader::load(std::string file, std::string levelName){
		std::fstream f(file);
		std::vector<std::string> lines;
		std::string temp;
		while(f>>temp){ lines.push_back(temp); }
		f.close();

		Level newLevel;

		for(int i = 0; i < lines.size(); ++i){
			for(int j = 0; j < lines[i].size(); ++j){
				switch(lines[i][j]){
					case 'B':
						newLevel.barricades.push_back(Barricade(j*35,i*35,35,35));
						break;
					case '@':
						newLevel.pX=j*30;
						newLevel.pY=i*30;
						break;
					case 'Z':
						newLevel.zombieSpawners.push_back(Spawner<Zombie>(nullptr, 15, j*30, i*30, 4));
						break;
					case '#':
						newLevel.walls.push_back(Wall(j*35,i*35, 35, 35));
						break;
					// m4a1
					case 'm':
						{
							game::Wall m4a1_wall = Wall(j*35,i*35,35,35, 1500);
							m4a1_wall.wallWeapon = game::GunManager::getInstance()->get("M4A1");
							newLevel.walls.push_back(m4a1_wall);
						}				
						break;
					default:
						break;
				}
			}
		}
		levels.insert(std::make_pair(levelName, newLevel));
	}
};
