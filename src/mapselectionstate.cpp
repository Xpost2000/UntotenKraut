#include "mapselectionstate.h"
#include "gamestate.h"
#include "fsm.h"
#include "texturemanager.h"

MapSelectionState::MapSelectionState(){
	blob = core::gfx::Sprite(0,0,0,0);
	smog = core::gfx::Sprite(0, 0, 0, 0);
	preview = core::gfx::Sprite(470, 150, 530, 400);
	smog.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\smog.png"));
	blob.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\ui_blob.png"));
	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );

	inputManager.AddCallback(
			SDL_MOUSEBUTTONDOWN,
			[&](SDL_Event& evnt){
			}
	);

	backButton = GUIButton( 0, 728, "Return To Menu", 20, 1, 1, 1, 1 );
// handy dandy macro
#define MapButton( x, y, name, path, internalName ) std::make_pair<std::string, std::pair<std::string, GUIButton>>(std::string(internalName), std::make_pair<std::string, GUIButton>( std::string(path), GUIButton(x,y, name, 20, 1, 1, 1, 1) ))
	// amazing! It works!
	mapButtons.insert(MapButton(0, 150, "Little Little Bunker,", "maps\\test.txt", "test"));
}

MapSelectionState::~MapSelectionState(){
}

void MapSelectionState::update(float dt){
	SDL_SetRelativeMouseMode(SDL_FALSE);

	if(backButton.isClicked(inputManager)){
		parent->setCurrentState("menu");
	}

	x1+=15*dt;
	x2+=30*dt;
	x3+=7*dt;

	for(auto& button : mapButtons){
		if(button.second.second.isMousedOver(inputManager)){
			preview.setTexture(core::TextureManager::getInstance()->getTexture("assests\\map_preview\\"+button.first));
		}
		if(button.second.second.isClicked(inputManager)){
			GameState* ptr = (GameState*)parent->getState("game");
			ptr->loadLevel(button.second.first, button.first);
			parent->setCurrentState("game");
		}
	}

	inputManager.Update();
}

void MapSelectionState::draw(core::gfx::Renderer& renderer){
	screen = core::gfx::Sprite(0, 0, renderer.getScreenWidth(), renderer.getScreenHeight());
	screen.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\menu.png"));
	renderer.identityCamera();
	renderer.refreshCamera();
	smog.setW(renderer.getScreenWidth());
	smog.setH(renderer.getScreenHeight());

	if(x1 > renderer.getScreenWidth()){
		x1=0;
	}if(x2 > renderer.getScreenWidth()){
		x2=0;
	}if(x3 > renderer.getScreenWidth()){
		x3=0;
	}
	
	// I could make a particle engine for this but eh.

	renderer.drawRect(0,0,0,0);
	renderer.drawSprite(screen);
	renderer.setTextSize(120);
	renderer.drawText("ocr", 0, 0, "Map Selection");
	smog.setX(0);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	smog.setX(x1);
	renderer.drawSprite(smog, 1, 1, 1, 0.1);
	smog.setX(x2);
	renderer.drawSprite(smog, 0.5, 0.4, 0.5, 0.2);
	smog.setX(x3);
	renderer.drawSprite(preview);
	renderer.setTextSize(15);
	renderer.drawText("ocr", 470, 130, "Currently Selected.");
	renderer.drawSprite(smog, 1, 1, 1, 0.2);

	for(auto& button : mapButtons){
		button.second.second.draw(renderer, &blob);
	}

	backButton.draw(renderer, &blob);
}
