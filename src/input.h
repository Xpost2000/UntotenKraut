#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <functional>

#include <SDL2/SDL.h>

namespace core{
	// Stores information pertaining to the Controller's joysticks
	// it helps make handling events related to it easier.
	struct JoystickAxisEvent{
		int right_vertical  =0;
		int right_horizontal=0;

		int left_vertical   =0;
		int left_horizontal =0;
	};

	struct JoystickTriggerEvent{
		int right_vertical  =0;
		int left_vertical   =0;
	};
	class InputManager{
		public:
			InputManager();
			~InputManager();			

			void Update();

			const bool isKeyDown( int key );
			const bool isButtonDown( int button );

			const bool RegisterController();
			const int  CheckForController(); // returns the amount of controllers SDL reports to us.

			const JoystickAxisEvent GetJoystickState();
			const JoystickTriggerEvent GetTriggerState();

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