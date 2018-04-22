#include "fsm.h"
#include "texturemanager.h"
#include "editorstate.h"
#include "gamestate.h"
#include <iostream>

EditorState::EditorState(){
	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );
	player = game::Player(0, 0, 30, 30, 15, 100);
	player.setGuns(game::GunManager::getInstance()->get("M1911A1"), game::GunManager::getInstance()->get("KAR98"));
	player.useGun(0);
	world.setPlayer(&player);
	textures = core::TextureManager::getInstance()->getTextures().size();
	guns = game::GunManager::getInstance()->getGuns().size();

	std::cout << "I report " << textures << " Textures loaded" << std::endl;
	lvlLoader.loadNew("editor//level.lvl", "EDITOR_ID");
	world.loadLevel(lvlLoader.getLevel("EDITOR_ID"));
}

EditorState::~EditorState(){

}

void EditorState::update(float dt){
	SDL_SetRelativeMouseMode(SDL_FALSE);
	if(inputManager.isKeyDown(SDL_SCANCODE_ESCAPE)){
		parent->setCurrentState("menu");
	}
	mouseInWorld = renderer->mouseToWorld(inputManager.GetMouseX(), inputManager.GetMouseY());
	// I know I just broke a rule, but the way I "designed" the renderer forces me to do this. I could change it later though
	if(inputManager.isKeyDown(SDL_SCANCODE_W)){
		renderer->translateCamera(0, 20*dt);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_S)){
		renderer->translateCamera(0, -20*dt);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_A)){
		renderer->translateCamera(20*dt, 0);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_D)){
		renderer->translateCamera(-20*dt, 0);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_P)){
		SDL_Delay(1500);
		writeToDisk("editor\\level.lvl");
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_R)){
		renderer->camX=0;
		renderer->camY=0;
		renderer->refreshCamera();
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_T)){
		testLevel();
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_X)){
		editingAGrid=!editingAGrid;
		SDL_Delay(10);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_1)){
		blockType=1;
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_2)){
		blockType=2;
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_3)){
		blockType=3;
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_4)){
		blockType=4;
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_G)){
		blockType=6;
		SDL_Delay(120);
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_B)){
		blockType=5;
		SDL_Delay(120);
	}
	if(editingAGrid){
		if(inputManager.isKeyDown(SDL_SCANCODE_LEFT)){
			if(w >= 0)
			w-=35;
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_RIGHT)){
			w+=35;
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_DOWN)){
			h+=35;
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_UP)){
			if(h >= 0)
			h-=35;
		}
		h= std::max<float>(h, 0);
		w= std::max<float>(w, 0);
	}else{
		if(inputManager.isKeyDown(SDL_SCANCODE_LEFT)){
			if(textureIndex >= 0 && textureIndex!=-1)
			textureIndex--;
			SDL_Delay(100);
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_RIGHT)){
			if(textureIndex <= textures)
			textureIndex++;
			SDL_Delay(100); // this is an artifical fix.
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_UP)){
			if(gunIndex <= guns)
			gunIndex++;
			SDL_Delay(100);
		}
		if(inputManager.isKeyDown(SDL_SCANCODE_DOWN)){
			if(gunIndex >= 0 && gunIndex!=-1)
			gunIndex--;	
			SDL_Delay(100); // this is an artifical fix.
		}
	}
	if(inputManager.isMouseKeyDown(SDL_BUTTON_LEFT)){
		// this is basically where most of it comes down to.
		mouseInWorld = renderer->mouseToWorld(inputManager.GetMouseX(), inputManager.GetMouseY());
		// snaps it to a grid of 35 which the game runs with
		int mX=round(mouseInWorld.x/35)*35;
		int mY=round(mouseInWorld.y/35)*35;
		game::Entity mouseCollideObj(mX, mY, 35, 35);
		if(blockType != 2){
		for(auto &w : world.getWalls()){
			if(mouseCollideObj.touching(w)){
				std::cout << "Touching wall" << std::endl;
				return;
			}
		}
		for(auto &ze : world.getSpawner()){
			game::Entity collideObj(ze.x, ze.y, 35, 35);
			if(mouseCollideObj.touching(collideObj)){
				std::cout << "Touching Spawner" << std::endl;
				return;
			}
		}
		for(auto &bar : world.getBarricades()){
			if(mouseCollideObj.touching(bar)){
				std::cout << "Touching Barricade" << std::endl;
				return;
			}
		}
		}
		switch(blockType){
			case 1:
				if((mX >= 0 && mX <= w) && (mY >= 0 && mY <= h)){
					world.addWall(game::Wall(mX,mY,35,35, core::TextureManager::getInstance()->getTextures()[textureIndex].second));
				}
				break;
			case 3:
				if((mX >= 0 && mX <= w) && (mY >= 0 && mY <= h)){
				world.addSpawner(mX, mY, 15, 2);
				}
				break;
			case 4:
				if((mX >= 0 && mX <= w) && (mY >= 0 && mY <= h)){
				player.x=mX;
				player.y=mY;
				}
				break;
			case 2:
				world.addDetail(game::DetailEntity(mX,mY,35,35, core::TextureManager::getInstance()->getTextures()[textureIndex].second));
				break;
			case 5:
				if((mX >= 0 && mX <= w) && (mY >= 0 && mY <= h)){
					world.addBarricade(game::Barricade(mX,mY,35,35));//, core::TextureManager::getInstance()->getTextures()[textureIndex].second));
				}
				break;
			case 6:
				if((mX >= 0 && mX <= w) && (mY >= 0 && mY <= h)){
					world.addWall(game::Wall(mX, mY, 35, 35, core::TextureManager::getInstance()->getTextures()[textureIndex].second, game::GunManager::getInstance()->getGuns()[gunIndex].second));
				}
				break;
		}
	SDL_Delay(100);
	}else if(inputManager.isMouseKeyDown(SDL_BUTTON_RIGHT)){
		int mX=round(mouseInWorld.x/35)*35;
		int mY=round(mouseInWorld.y/35)*35;
		game::Entity mouseCollideObj(mX, mY, 35, 35);
		for(int i = 0; i < world.getWalls().size(); ++i){
			auto& w = world.getWalls()[i];
			if(mouseCollideObj.touching(w)){
				std::cout << "deleting wall" << std::endl;
				world.getWalls().erase(world.getWalls().begin()+i);	
				return;
			}
		}
		for(int i = 0; i < world.getSpawner().size(); ++i){
			auto& ze = world.getSpawner()[i];
			game::Entity mouseCollideObj(mX, mY, 35, 35);
			game::Entity collideObj(ze.x, ze.y, 35, 35);
			if(mouseCollideObj.touching(collideObj)){
				world.getSpawner().erase(world.getSpawner().begin()+i);
				std::cout << "deleting Spawner" << std::endl;
				return;
			}
		}
		for(int i = 0 ; i < world.getBarricades().size(); ++i){
			auto& bar = world.getBarricades()[i];
			if(mouseCollideObj.touching(bar)){
				std::cout << "deleting Barricade" << std::endl;
				world.getBarricades().erase(world.getBarricades().begin()+i);
				return;
			}
		}
	}

	inputManager.Update();
}

// easy convenience function.
std::string EditorState::genNameFromType(){
	switch(blockType){
		case 1:
			return "Solid";
			break;
		case 2:
			return "Detail";
			break;
		case 3:
			return "ZombieSpawner";
			break;
		case 4:
			return "PlayerLocation";
			break;
		case 5:
			return "Barricade";
			break;
		case 6:
			return "Gun Wall";
			break;
	}
}

void EditorState::draw(core::gfx::Renderer& renderer){
	if(this->renderer==nullptr)
	this->renderer=&renderer; // this line was to hack something together lol
	if(editingAGrid)
	renderer.drawRect(0, 0, w, h, 0.8, 0.1, 0.1, 0.4);
	else
	renderer.drawRect(0, 0, w, h, 0.3, 0.1, 0.1, 0.4);
	// grammar error
	for(auto &zsp : world.getSpawner()){
		renderer.drawRect(zsp.x, zsp.y, 35, 35, 0.1, 0.9, 0.1, 1.0);
	}
	world.draw(renderer);
// preview object
	mouseInWorld = renderer.mouseToWorld(inputManager.GetMouseX(), inputManager.GetMouseY());
	// snaps it to a grid of 35 which the game runs with
	int mX=round(mouseInWorld.x/35)*35;
	int mY=round(mouseInWorld.y/35)*35;
	renderer.drawRect(mX, mY, 35, 35, 1, 1, 1, 1);
	renderer.setTextSize(11);
	renderer.drawText("ocr", 0, 0, "Editor Mode (P saves the level as level.lvl(TODO: IMPLEMENT NAMING))");
	renderer.drawText("ocr", 0, 15, "(Use R to reset camera, Use T to test level, X set A* world dimensions, B set to barricade, G set gun wall)(Number Keys 1 - 4 for block type, arrow keys select texture.)");
	renderer.drawText("ocr", 0, 30, "Current Block Type : " + genNameFromType() );
	// hope it works.
	renderer.drawText("ocr", 0, 45, "Texture Path : " + core::TextureManager::getInstance()->getTextures()[textureIndex].first + "("+std::to_string(textureIndex)+")" );
	renderer.drawText("ocr", 0, 60, "Current Gun : " + game::GunManager::getInstance()->getGuns()[gunIndex].first + "("+std::to_string(gunIndex)+")" );
	if(editingAGrid)
	renderer.drawText("ocr", 0, 60, "A* Grid Editing Mode On(press X again to leave)");


	renderer.refreshCamera();


}

void EditorState::writeToDisk(std::string filename){
	std::ofstream levelFile(filename);
	levelFile << "agrid " << w << " " << h << std::endl;
	levelFile << "playerPos " << world.getPlayer()->x << " " << world.getPlayer()->y << std::endl;
	for(auto& wall : world.getWalls()){
		if(wall.getHasGun()){
			levelFile << "gunwall " << wall.x << " " << wall.y << " " << wall.getTex()->path << " " << wall.getWallWeapon().getName() << std::endl;
		}else{
			levelFile << "wall " << wall.x << " " << wall.y << " " << wall.getTex()->path << std::endl;
		}
	}
	for(auto& detail : world.getDetailEntities()){
			levelFile << "detail " << detail.x << " " << detail.y << " " << detail.getTex()->path << std::endl;
	}
	for(auto& spawner : world.getSpawner()){
			levelFile << "zspawner " << spawner.x << " " << spawner.y << std::endl; 
	}
	for(auto& bar : world.getBarricades()){
			levelFile << "barricade " << bar.x << " " << bar.y << std::endl;
	}
}

void EditorState::testLevel(){
	world.getWidth() = w;
	world.getHeight() = h;
	GameState *state = (GameState*)parent->getState("game");
	state->world = world;
	state->world.reinitSpawners();
	state->player.x=player.x;
	state->player.y=player.y;
	state->world.setPlayer(&state->player);
	state->prepareGame();
	parent->setCurrentState("game");
}
