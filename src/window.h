#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace core{
	/*
	 * This class is ment to be a simple SDL2 window wrapper.
	 * It literally only just makes a window with an opengl context.
	 */
	class Window{
		public:
			Window( std::string name, int width, int height );
			Window();
			~Window();

			void Create( std::string name, int width, int height );	
			void Refresh();

			SDL_Window* GetHandle(){ return m_windowHandle; }
			int& getSwapInterval(){ return m_swapInterval; }
		private:
			std::string name="";
			
			SDL_Window* m_windowHandle = nullptr;
			SDL_GLContext m_context;

			int m_swapInterval=1;
	};
};

#endif
