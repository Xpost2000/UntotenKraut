#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>

#include "window.h"
#include "input.h"

int main( int argc, char** argv ){
	bool runProgram=true;

	SDL_Init(SDL_INIT_EVERYTHING);
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
			[&](){
				runProgram=false;
			}
		    );

	while(runProgram){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3, 0.3, 0.3, 1.0);
		if(inputManager.isKeyDown( SDL_SCANCODE_A )){
			std::cout << "A key pressed" << std::endl;
		}
		if(inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_A )){
			std::cout << "A(x on playstation) Down" << std::endl;
		}
		inputManager.Update();
		window.Refresh();
	}

	SDL_Quit();
	return 0;
}
