#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

namespace core{
	class InputManager{
		public:
			InputManager();
			~InputManager();			

			void Update();

			bool isKeyDown( int key );
			bool isButtonDown( int button );

			bool CheckForController();

			const int GetMouseX() { return m_mX; }
			const int GetMouseY() { return m_mY; }
		private:
			// todo: add callbacks and stuff.
			const uint8_t* m_keys;
			uint8_t m_buttons[SDL_CONTROLLER_BUTTON_MAX+1]; // for controllers.

			int m_mX=0, m_mY=0;

			SDL_Event m_event;
			SDL_GameController* m_controller=nullptr;
	};
};
#endif
