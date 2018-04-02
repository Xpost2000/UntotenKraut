#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

#include "window.h"
#include "sound.h"
#include "input.h"
#include "shader.h"
#include "renderer.h"
#include "sprite.h"

#include "world.h"

#include "wall.h"
#include "player.h"

#include "texturemanager.h"
#include "gunmanager.h"

#include "gui_text.h"
#include "gui_button.h"

#include "gamestate.h"
#include "menustate.h"
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
	bool runProgram=true;
	core::Window window;
	core::InputManager inputManager;

	window.Create( 
		       "Test"  ,
		       1024    ,
		       768 
		     );

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				runProgram=false;
			}
		    );
	core::gfx::Renderer renderer(1024, 768);
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_512_tset.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_barricade_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_projectile.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_zombie_test.png");

	renderer.loadFont("ocr.ttf",   "ocr");
	renderer.loadFont("arial.ttf", "arial");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game::GunManager::getInstance()->addGun("M1911A1", game::Gun("M1911A1", 9, 30, 500, 3, false, 14, 7, 2));
	game::GunManager::getInstance()->addGun("M4A1", game::Gun("M4A1", 12, 30, 600, 1.5, true, 200, 30, 3));

	StateMachine stateMachine;
	GameState gameState;
	MenuState menuState;
	stateMachine.addState(&gameState, "game");
	stateMachine.addState(&menuState, "menu");
	stateMachine.setCurrentState("menu");
#ifdef TESTING_MACHINE
	while(true){
		stateMachine.update(10);
	}
#endif
	while(runProgram){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		stateMachine.update(0.1f);
		stateMachine.draw(renderer);
		inputManager.Update();
		window.Refresh();
	}
	core::audio::SoundManager::getInstance()->free();	
	core::TextureManager::getInstance()     ->free();
	return 0;
}
