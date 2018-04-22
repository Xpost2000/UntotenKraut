#include "levelloader.h"
#include "texturemanager.h"
namespace game{
	//size is 30
	void LevelLoader::loadNew(std::string file, std::string levelName){
		if(levels.count(levelName)) { return; }
		std::fstream f(file);
		if(!f.good()){return;}
		std::string processStr;
		Level newLevel;
		float x=0;
		float y=0;
		std::string path;
		std::string gunName;
		while(f >> processStr){
			if(processStr == "agrid"){
				f >> newLevel.w;
				f >> newLevel.h;
				newLevel.w/=35;
				newLevel.h/=35;
			}
			if(processStr == "playerPos"){
				f>>newLevel.pX;
				f>>newLevel.pY;
			}
			if(processStr == "barricade"){
				f>>x;
				f>>y;
				newLevel.barricades.push_back(Barricade(x,y,35,35));
			}
			if(processStr == "detail"){
				f>>x;
				f>>y;
				f>>path;
				newLevel.detail_ents.push_back(DetailEntity(x,y,35,35,core::TextureManager::getInstance()->getTexture(path)));
			}
			if(processStr == "gunwall"){
				f>>x;
				f>>y;
				f>>path;
				f>>gunName;
				newLevel.walls.push_back(Wall(x, y, 35, 35, core::TextureManager::getInstance()->getTexture(path), game::GunManager::getInstance()->get(gunName)));
			}
			if(processStr == "wall"){
				f>>x;
				f>>y;
				f>>path;
				newLevel.walls.push_back(Wall(x, y, 35, 35, core::TextureManager::getInstance()->getTexture(path)));
			}
			if(processStr == "zspawner"){
				f>>x;
				f>>y;
				newLevel.zombieSpawners.push_back(Spawner<Zombie>(nullptr, 15, x, y, 1));
			}
		}
		levels.insert(std::make_pair(levelName, newLevel));
	}
	void LevelLoader::load(std::string file, std::string levelName){
		if(levels.count(levelName)) { return; }
		std::fstream f(file);
		std::vector<std::string> lines;
		std::string temp;
		while(f>>temp){ lines.push_back(temp); }
		f.close();

		Level newLevel;

		newLevel.h = lines.size();
		newLevel.w = lines[0].size(); // A proper level should appear to be a convex shape so this is acceptable.
		for(int i = 0; i < lines.size(); ++i){
			for(int j = 0; j < lines[i].size(); ++j){
				switch(lines[i][j]){
					case '[':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_cl.png")));
						break;
					case ']':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_cr.png")));
						break;
					case '<':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_clb.png")));
						break;
					case '>':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_crb.png")));
						break;
					case 'B':
						newLevel.barricades.push_back(Barricade(j*35,i*35,35,35));
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud.png")));
						break;
					case '@':
						newLevel.pX=j*30;
						newLevel.pY=i*30;
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\floor.png")));
						break;
					case 'Z':
						newLevel.zombieSpawners.push_back(Spawner<Zombie>(nullptr, 15, j*35, i*35, 2));
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud.png")));
						break;
					case 'X':
						newLevel.walls.push_back(Wall(j*35,i*35, 35, 35, core::TextureManager::getInstance()->getTexture("assests\\textures\\concrete.png")));
						break;
					case '#':
						newLevel.walls.push_back(Wall(j*35,i*35, 35, 35, core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_wall_test.png")));
						break;
					// m4a1
					case 'm':
						{
							game::Wall m4a1_wall = Wall(j*35,i*35,35,35, core::TextureManager::getInstance()->getTexture("assests\\textures\\dev_wallbuy_test.png"), 1500);
							m4a1_wall.wallWeapon = game::GunManager::getInstance()->get("M4A1");
							newLevel.walls.push_back(m4a1_wall);
						}				
						break;
					case ',':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\mud.png")));
						break;
					case '.':
						newLevel.detail_ents.push_back(DetailEntity(j*35,i*35,35,35,core::TextureManager::getInstance()->getTexture("assests\\textures\\floor.png")));
						break;
					default:
						break;
				}
			}
		}
		levels.insert(std::make_pair(levelName, newLevel));
	}
};
