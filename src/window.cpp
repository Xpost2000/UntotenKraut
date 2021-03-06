#include "window.h"
#include <GL/glew.h>
#include <iostream>


namespace core{
	Window::Window( std::string name, int width, int height ){
		Create( name, width, height );
	}
	
	Window::Window(){
	}

	Window::~Window(){
		if(m_windowHandle){
			SDL_DestroyWindow(m_windowHandle);
		}
		SDL_GL_DeleteContext(m_context);
	}

	void Window::Create( std::string title, int width, int height ){
		m_windowHandle = SDL_CreateWindow(
					title.c_str(),
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height,
					SDL_WINDOW_OPENGL
		);
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION , 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION , 3 );
		SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL    , 1 );

		m_context = SDL_GL_CreateContext(m_windowHandle);
#ifdef __linux__
		// glewExperimental needs to be on for the version of GLEW I have on linux
		glewExperimental = true;
#endif
		if(glewInit()!=GLEW_OK){
			std::cout << "GLEW Failed to Init... ABORT!" << std::endl;
			return;	
		}

		SDL_GL_SetSwapInterval(m_swapInterval);
		SDL_GL_MakeCurrent(m_windowHandle, m_context);
	}

	void Window::Refresh(){
		SDL_GL_SwapWindow(m_windowHandle);
	}
};
