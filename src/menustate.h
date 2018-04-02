#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "state.h"
#include "input.h"
#include "gui_button.h"

class MenuState : public State{
	public:
		MenuState();
		~MenuState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		core::InputManager inputManager;

		GUIButton startButton;
};

#endif
