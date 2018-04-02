#ifndef STATE_H
#define STATE_H

#include "renderer.h"

class StateMachine;
class State{
	public:
		State(){}
		~State(){}

		virtual void update(float dt){};
		virtual void draw(core::gfx::Renderer&){};
	protected:
		friend class StateMachine;
		StateMachine* parent;
};

#endif
