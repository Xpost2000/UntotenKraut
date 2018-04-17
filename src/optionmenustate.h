#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H
#include "state.h"
#include "input.h"
#include "gui_button.h"
#include "sprite.h"

class OptionMenuState : public State{
	public:
		OptionMenuState();
		~OptionMenuState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		float x1=0,x2=0,x3=0;
		bool fs=false;

		core::InputManager inputManager;
		core::gfx::Sprite blob;
		core::gfx::Sprite smog;
		core::gfx::Sprite screen; // the background.

		GUIButton fullscreenButton, backButton;
};

#endif
