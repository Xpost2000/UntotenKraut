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

int main( int argc, char** argv ){
	bool runProgram=true;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	Mix_Init(MIX_INIT_MP3);
	glewInit();
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
	//Testing something here...
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_512_tset.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_barricade_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_projectile.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_zombie_test.png");
	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\M4A1_fire.wav", "M4A1_fire");
	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\M4A1_reload.wav", "M4A1_reload");
	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\M1911A1_fire.wav", "M1911A1_fire");
	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\M1911A1_reload.wav", "M1911A1_reload");
	game::Player player(0, 0, 30, 30, 15, 100);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderer.loadFont("arial.ttf", "arial");
	renderer.loadFont("ocr.ttf",   "ocr");

	game::World world;
	// TODO: make gun manager class to deal with guns.
	game::Gun pistol("M1911A1", 9, 30, 500, 3, false, 14, 7, 2);
	game::Gun smg("M4A1", 12, 30, 600, 1.5, true, 200, 30, 3);

	player.getGun() = pistol;

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
			player.getGun() = pistol;
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_2 ) ){
			player.getGun() = smg;
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
		renderer.setTextSize(20);
		renderer.drawText( "arial", 0, 0, "Current Gun : " + player.getGun().getName(), 1,1,1,1 );
		renderer.drawText( "arial", 0, 20, std::to_string(player.getGun().getCurrentCapacity()) + "/"+ std::to_string(player.getGun().getMaxCapacity()), 1,1,1,1 );
		renderer.setTextSize(15);
		renderer.drawText( "arial", inputManager.GetMouseX(), inputManager.GetMouseY() , "mousePos", 1,1,1,1 );

		world.draw(renderer);
		world.update(0.1f);

		// TODO: Make gui elements...
		renderer.drawRect(1024-100, 768-100, 100, 20, 1, 0, 0, 1);
		renderer.setTextSize(13);
		renderer.drawText("arial", 1024-100, 768-97, "Score: " + std::to_string(world.getScore()), 1, 1, 1, 1);
		}else{
			renderer.setTextSize(40);
			renderer.drawText("arial", 0, 0, "Player has died...", 1, 0, 0, 1);
			renderer.drawText("arial", 0, 43, "Final Score : " + std::to_string(world.getScore()), 1, 1, 1, 1);
		}

		inputManager.Update();
		window.Refresh();
	}
	core::audio::SoundManager::getInstance()->free();	
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}
