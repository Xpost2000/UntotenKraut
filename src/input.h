#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <functional>

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

			void AddCallback( int event, std::function<void(SDL_Event& evnt)> function );
		private:
			std::unordered_map< int, std::function<void(SDL_Event& evnt)> > m_callbacks;
			// todo: add callbacks and stuff.
			const uint8_t* m_keys;
			uint8_t m_buttons[SDL_CONTROLLER_BUTTON_MAX] = {0}; // for controllers.

			int m_mX=0, m_mY=0;

			SDL_Event m_event;
			SDL_GameController* m_controller=nullptr;
	};
};
#endif
