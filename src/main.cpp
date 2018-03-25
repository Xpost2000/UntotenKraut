#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "window.h"
#include "input.h"
#include "shader.h"
#include "renderer.h"

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
	core::Renderer renderer(1024, 768);
	while(runProgram){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3, 0.3, 0.3, 1.0);
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
		renderer.drawRect(0, 0, 150, 150, 1.0, 0, 0, 1.0);
		inputManager.Update();
		window.Refresh();
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}
