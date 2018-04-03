#ifndef QUIT_STATE_H
#define QUIT_STATE_H

#include "state.h"

/*
 * Dummy state
 * just so I don't get complaints about an abstract class.
 */

class QuitState : public State{
	public:
		QuitState(){}
		~QuitState(){}
		void update(float dt){dt*=1;}
		void render(core::gfx::Renderer& renderer){renderer.refreshCamera();}
	private:
};

#endif
