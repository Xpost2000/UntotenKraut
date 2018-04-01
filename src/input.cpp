#include "input.h"

#include <cstdio>

namespace core{
	InputManager::InputManager(){
		if( RegisterController() ){
			fprintf(stderr, "controller found : %s\n", SDL_GameControllerName( m_controller ));
		}else{
			fprintf(stderr, "No controller found...\n");
		}
	}
	
	InputManager::~InputManager(){
		SDL_GameControllerClose( m_controller );
	}	

	const int InputManager::CheckForController(){
		return SDL_NumJoysticks();
	}

	const bool InputManager::RegisterController(){
		fprintf(stderr, "Joysticks : %d\n", SDL_NumJoysticks());
		// search for the first "controller"
		if( CheckForController() >= 1 ){
			for(int i = 0; i < SDL_NumJoysticks(); ++i){
				if(SDL_IsGameController(i)){	
					m_controller = SDL_GameControllerOpen( i );
					return true;
				}else{
					m_controller = nullptr;
					return false;
				}
			}
		}
		return false;
	}

	void InputManager::AddCallback( int event, std::function<void(SDL_Event& event)> function ){
		m_callbacks[event] = function;
	}

	void InputManager::Update(){
		while( SDL_PollEvent( &m_event ) ){
			if(m_callbacks.find(m_event.type) != m_callbacks.end()){
				m_callbacks[m_event.type](m_event);
			}
		}
		SDL_GetMouseState(&m_mX, &m_mY);
		m_keys = SDL_GetKeyboardState( NULL );
		if(m_controller != nullptr){
			for( int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i ){
				m_buttons[i] = SDL_GameControllerGetButton( m_controller, (SDL_GameControllerButton)i );
			}
		}
	}

	const bool InputManager::isMouseKeyDown( int bitmask ){
		return(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(bitmask));
	}
	const bool InputManager::isKeyDown( int key ){
		if(m_keys==nullptr){return false;}
		return m_keys[key];
	}

	const bool InputManager::isButtonDown( int button ){
		if(m_keys==nullptr){return false;}
		return m_buttons[button];
	}

	const JoystickAxisEvent InputManager::GetJoystickState(){
		JoystickAxisEvent axis;
		if( m_controller != nullptr ){
			axis.left_horizontal  = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_LEFTX );
			axis.left_vertical    = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_LEFTY );

			axis.right_horizontal = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_RIGHTX );
			axis.right_vertical   = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_RIGHTY );

			// downscale it to out of 255 / 256
			// by dividing by 128.
			axis.left_horizontal   /=128;
			axis.left_vertical     /=128;
			axis.right_horizontal  /=128;
			axis.right_vertical    /=128;
		}
		return axis;
	}

	const JoystickTriggerEvent InputManager::GetTriggerState(){
		JoystickTriggerEvent triggers;
		if( m_controller != nullptr ){
			triggers.left_vertical  = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT );	
			triggers.right_vertical = SDL_GameControllerGetAxis( m_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT );
			// read the above in ::GetJoystickState()
			triggers.left_vertical  /=128;
			triggers.right_vertical /=128;
		}
		return triggers;

	}
};
