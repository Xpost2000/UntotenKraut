#include <GL/glew.h>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <fstream>
#include <iostream>

#include "window.h"
#include "sound.h"
#include "input.h"
#include "renderer.h"

#include "texturemanager.h"
#include "gunmanager.h"

#include "gamestate.h"
#include "menustate.h"
#include "deathstate.h"
#include "editorstate.h"
#include "quitstate.h"
#include "mapselectionstate.h"
#include "fsm.h"


extern "C"{
	void _atExit(void){
		printf("Freeing sdl resources...\n");
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();	
	}
}

int main( int argc, char** argv ){
	atexit(_atExit);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	Mix_Init(MIX_INIT_MP3);
	core::Window window;
	core::InputManager inputManager;

	window.Create( 
		       "Untoten Kraut"  ,
		       1024    ,
		       768 
		     );
	core::gfx::Renderer renderer(1024, 768);
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_512_tset.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_barricade_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_wallbuy_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_projectile.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\ui\\ui_stain.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_zombie_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\test_ground.png");

	renderer.loadFont("assests\\fonts\\ocr.ttf",   "ocr");
	renderer.loadFont("assests\\fonts\\arial.ttf", "arial");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game::GunManager::getInstance()->addGun("KAR98", game::Gun("KAR98", 30, 50, 800, 3, false, 70, 5, 3 ));
	game::GunManager::getInstance()->addGun("M1911A1", game::Gun("M1911A1", 9, 30, 500, 1.4, false, 80, 7, 2.25));
	game::GunManager::getInstance()->addGun("M4A1", game::Gun("M4A1", 12, 30, 600, 1, true, 300, 30, 1.3));

	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\round_end.wav", "round_end");

	StateMachine stateMachine;
	GameState gameState;
	DeathState deathState;
	EditorState editorState;
	MenuState menuState;
	MapSelectionState mapSelectionState;
	QuitState quitState;

	stateMachine.addState(&gameState, "game");
	stateMachine.addState(&menuState, "menu");
	stateMachine.addState(&quitState, "quit");
	stateMachine.addState(&deathState, "death");
	stateMachine.addState(&editorState, "editor");
	stateMachine.addState(&mapSelectionState, "mapselect");
	stateMachine.setCurrentState("menu");

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				stateMachine.setCurrentState("quit");
			}
	 );
	Uint32 start = 0;
	Uint32 end   = 0;
	float dt = 0;
	while( stateMachine.getCurrentState() != &quitState ){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		start = SDL_GetTicks();
		dt = (start-end)/1000.0f;
		end = start;

		stateMachine.update(dt);
		stateMachine.draw(renderer);
		inputManager.Update();
		window.Refresh();
	}
	SDL_SetRelativeMouseMode(SDL_FALSE);
	core::audio::SoundManager::getInstance()->free();	
	core::TextureManager::getInstance()     ->free();
	return 0;
}
