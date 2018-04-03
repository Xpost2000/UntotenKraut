#include "fsm.h"
#include "editorstate.h"
#include "gamestate.h"

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
	if(inputManager.isKeyDown(SDL_SCANCODE_R)){
		renderer->camX=0;
		renderer->camY=0;
		renderer->refreshCamera();
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_T)){
		testLevel();
	}
	if(inputManager.isMouseKeyDown(SDL_BUTTON_LEFT)){
	}
	inputManager.Update();
}

void EditorState::draw(core::gfx::Renderer& renderer){
	if(this->renderer==nullptr)
	this->renderer=&renderer;
	renderer.setTextSize(15);
	renderer.drawText("ocr", 0, 0, "Editor Mode: CameraPos( " + std::to_string(renderer.camX) + " , " + std::to_string(renderer.camY) + " )");
	renderer.drawText("ocr", 0, 15, "(Use R to reset camera, Use T to test level)**INSTRUCTIONS HERE**");

	renderer.refreshCamera();

	world.draw(renderer);
}

void EditorState::writeToDisk(std::string filename){
	// need to think of a format to write as.
}

void EditorState::testLevel(){
	GameState *state = (GameState*)parent->getState("game");
	state->world = world;
	state->player.x=player.x;
	state->player.y=player.y;
	state->world.setPlayer(&state->player);
	parent->setCurrentState("game");
}
