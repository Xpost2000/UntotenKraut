#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include "renderer.h"
#include <unordered_map>

class State;
class StateMachine{
	public:
		StateMachine();
		~StateMachine();
		void addState(State*, std::string name);

		void update(float dt);
		void draw(core::gfx::Renderer&);

		void setCurrentState(std::string name);
		State* getState( std::string name ) { return states[name]; }
		State* getCurrentState(){ return currentState; }
		void* data=nullptr; // special data.
	private:
		friend class State;
		State* currentState=nullptr;
		std::unordered_map<std::string, State*> states;
};

#endif
