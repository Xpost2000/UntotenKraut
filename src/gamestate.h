#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"

class GameState : public State{
	public:
		GameState();
		~GameState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
};

#endif
