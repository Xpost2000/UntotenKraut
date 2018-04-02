#ifndef STATE_H
#define STATE_H

#include "renderer.h"

class State{
	public:
		State(){}
		~State(){}

		virtual void update(float dt)=0;
		virtual void draw(core::gfx::Renderer&)=0;
	private:
};

#endif
