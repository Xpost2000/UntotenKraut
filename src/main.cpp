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

extern "C"{
	void _atExit(void){
		printf("Freeing sdl resources...\n");
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();	
	}
}

int main( int argc, char** argv ){
	bool runProgram=true;
	atexit(_atExit);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	Mix_Init(MIX_INIT_MP3);
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


	game::Player player(0, 0, 30, 30, 15, 100);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderer.loadFont("arial.ttf", "arial");
	renderer.loadFont("ocr.ttf",   "ocr");

	game::World world;
	game::GunManager::getInstance()->addGun("M1911A1", game::Gun("M1911A1", 9, 30, 500, 3, false, 14, 7, 2));
	game::GunManager::getInstance()->addGun("M4A1", game::Gun("M4A1", 12, 30, 600, 1.5, true, 200, 30, 3));

	GUIText score_text(900, 700, "", 15), weapon_text(900, 720, "", 14);
	weapon_text.setBoxColor(1, 1, 1, 1);
	weapon_text.setTextColor(0, 0, 0, 1);
	score_text.setBoxColor(1, 0, 0, 1);
	score_text.setTextColor(1, 1, 1, 1);

	player.getGun() = game::GunManager::getInstance()->get("M1911A1");

	world.setPlayer(&player);
	world.addWall(game::Wall( 100, 200, 60, 60 ));
	world.addWall(game::Wall( 100, 500, 60, 60 ));
	world.addSpawner(300, 200, 30);
	world.addSpawner(600, 200, 30);
	world.addSpawner(800, 500, 30);
	bool reloading=false;
	while(runProgram){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		if(player.getHp() > 0){
		if( inputManager.isKeyDown( SDL_SCANCODE_W ) ){
			player.move(1, world);
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_S ) ){
			player.move(2, world);
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_A ) ){
			player.move(3, world);
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_D ) ){
			player.move(4, world);
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_1 ) ){
			player.getGun() = game::GunManager::getInstance()->get("M1911A1");
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_2 ) ){
			player.getGun() = game::GunManager::getInstance()->get("M4A1");
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_R ) ){
			reloading=true;
		}
		if(reloading){
			reloading=!player.getGun().reload(0.1f);
		}

		if( inputManager.isMouseKeyDown( SDL_BUTTON_LEFT ) ){
			if(!reloading)
			player.fire(inputManager.GetMouseX(), inputManager.GetMouseY());
		}
		if(inputManager.CheckForController()){
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_A ) ){
			}
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_B ) ){
			}
		}
		renderer.refreshCamera();

		world.draw(renderer);
		world.update(0.1f);

		// TODO: Make gui elements...
		score_text.setText("Score: "+ std::to_string(world.getScore()));
		weapon_text.setText(player.getGun().getName()+": " + std::to_string(player.getGun().getCurrentCapacity()) + "/" + std::to_string(player.getGun().getMaxCapacity()));
		score_text.draw(renderer);
		weapon_text.draw(renderer);
		}else{
			renderer.setTextSize(40);
			renderer.drawText("arial", 0, 0, "Player has died...", 1, 0, 0, 1);
			renderer.drawText("arial", 0, 43, "Final Score : " + std::to_string(world.getScore()), 1, 1, 1, 1);
		}

		inputManager.Update();
		window.Refresh();
	}
	core::audio::SoundManager::getInstance()->free();	
	core::TextureManager::getInstance()     ->free();
	return 0;
}
