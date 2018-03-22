#include "input.h"

#include <cstdio>

namespace core{
	InputManager::InputManager(){
		if( CheckForController() ){
			fprintf(stderr, "controller found\n");
		}else{
			fprintf(stderr, "No controller found...\n");
		}
	}
	
	InputManager::~InputManager(){
	}	

	bool InputManager::CheckForController(){
		fprintf(stderr, "Joysticks : %d\n", SDL_NumJoysticks());
		// search for the first "controller"
		if( SDL_NumJoysticks() >= 1 ){
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

	bool InputManager::isKeyDown( int key ){
		return m_keys[key];
	}

	bool InputManager::isButtonDown( int button ){
		return m_buttons[button];
	}
};
