#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "state.h"
#include "input.h"
#include "gui_button.h"
#include "sprite.h"

class MenuState : public State{
	public:
		MenuState();
		~MenuState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		float x1=0,x2=0,x3=0;

		core::InputManager inputManager;
		core::gfx::Sprite blob;
		core::gfx::Sprite smog;
		core::gfx::Sprite screen; // the background.

		GUIButton startButton, editModeButton, quitButton;
};

#endif
