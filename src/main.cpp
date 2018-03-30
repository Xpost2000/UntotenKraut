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

#include "player.h"

int main( int argc, char** argv ){
	bool runProgram=true;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	Mix_Init(MIX_INIT_MP3);
	glewInit();
	core::Window window;
	core::InputManager inputManager;
	core::audio::SoundManager soundManager;


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
	game::Player player(0, 0, 30, 30, 15, 100);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderer.loadFont("arial.ttf", "arial");
	renderer.loadFont("ocr.ttf",   "ocr");
	while(runProgram){
		soundManager.playSound( "test", -1, 100 );
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		if( inputManager.isKeyDown( SDL_SCANCODE_W ) ){
			player.y -= 4;
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_S ) ){
			player.y += 4;
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_A ) ){
			player.x -= 4;
		}
		if( inputManager.isKeyDown( SDL_SCANCODE_D ) ){
			player.x += 4;
		}
		if( inputManager.isMouseKeyDown( SDL_BUTTON_LEFT ) ){
			player.fire(inputManager.GetMouseX(), inputManager.GetMouseY());
		}
		if(inputManager.CheckForController()){
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_A ) ){
			}
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_B ) ){
			}
		}
		renderer.refreshCamera();
		renderer.setTextSize(40);
		renderer.drawText( "arial", 0, 0, "Player Test...", 0,0,1,1 );
		renderer.setTextSize(15);
		player.draw(renderer);
		renderer.drawText( "arial", player.x, player.y, "playerpos", 1,1,1,1 );
		renderer.drawText( "arial", inputManager.GetMouseX(), inputManager.GetMouseY() , "mousePos", 1,1,1,1 );

		player.update(0.1f);
		for(int i = 0; i < player.getBullets().size(); ++i){
			player.getBullets()[i].update( 0.1f );
			if(!player.getBullets()[i].isAlive()){
				player.getBullets().erase(player.getBullets().begin()+i);
			}

			player.getBullets()[i].draw(renderer);
		}

		inputManager.Update();
		window.Refresh();
	}
	soundManager.free();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	return 0;
}
