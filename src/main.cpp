#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>

#include "window.h"
#include "input.h"

int main( int argc, char** argv ){
	SDL_Init(SDL_INIT_EVERYTHING);
	glewInit();
	core::Window window;
	core::InputManager inputManager;

	window.Create( 
		       "Test"  ,
		       1024    ,
		       768 
		     );
	while(true){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3, 0.3, 0.3, 1.0);
		inputManager.Update();
		window.Refresh();
	}

	SDL_Quit();
	return 0;
}
