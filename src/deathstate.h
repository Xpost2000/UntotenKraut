#ifndef DEATH_STATE_H
#define DEATH_STATE_H

#include "state.h"

class DeathState : public State{
	public:
		DeathState(){}
		~DeathState(){}
		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		float countDown=100;
};

#endif
