#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "window.h"
#include "input.h"
#include "shader.h"
#include "renderer.h"
#include "sprite.h"

int main( int argc, char** argv ){
	bool runProgram=true;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
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
	core::gfx::Sprite   zed_test_image( 200, 300, 256, 256 );
	zed_test_image.loadTexture("assests\\textures\\dev_zombie_test.png");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	renderer.loadFont("arial.ttf", "arial");
	renderer.loadFont("ocr.ttf",   "ocr");
	while(runProgram){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		if( inputManager.isKeyDown( SDL_SCANCODE_A ) ){
			std::cout << "A key pressed" << std::endl;
		}
		if(inputManager.CheckForController()){
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_A ) ){
				std::cout << "A(X on playstation) Down" << std::endl;
			}
			if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_B ) ){
				std::cout << "B(O on playstation) Down" << std::endl;
			}
			if(inputManager.GetJoystickState().right_horizontal > 5)
				std::cout << "Joystick Right X: " << inputManager.GetJoystickState().right_horizontal << std::endl;
			if(inputManager.GetTriggerState().right_vertical > 5)
				std::cout << "Trigger Right : " << inputManager.GetTriggerState().right_vertical << std::endl;
		}
		renderer.refreshCamera();
		renderer.drawRect(0, 0, 150, 150, 1.0, 0, 1.0, 1.0);
		renderer.drawRect(60, 0, 150, 150, 0.0, 0.5, 0.3, 0.7);
		renderer.setTextSize(40);
		renderer.drawText( "arial", 0, 0, "abcdefghijklmnopqrstuvwxyz", 0,0,1,1 );
		renderer.drawText( "arial", 0, 50, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
		renderer.setTextSize(80);
		renderer.drawText( "ocr", 0, 100, "abcdefghijklmnopqrstuvwxyz", 1, 0, 0, 1 );
		renderer.drawText( "ocr", 0, 200, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 1, 0, 1 );
		zed_test_image.setX(200);
		zed_test_image.setY(300);
		renderer.drawSprite(zed_test_image);
		renderer.drawRect(300, 450, 150, 150, 0.0, 0.5, 1.0, 0.7);
		zed_test_image.setX(500);
		renderer.drawSprite(zed_test_image, 1, 1, 0, 0.4);
		inputManager.Update();
		window.Refresh();
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}
