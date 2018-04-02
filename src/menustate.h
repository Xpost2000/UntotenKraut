#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "state.h"

class MenuState : public State{
	public:
		MenuState();
		~MenuState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
};

#endif
