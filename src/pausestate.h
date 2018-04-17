#ifndef PAUSESTATE_H
#define PAUSESTATE_H
#include "sprite.h"
#include "input.h"
#include "gui_button.h"
#include "state.h"

class PauseState : public State{
	public:
		PauseState();
		~PauseState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		float x1=0,x2=0,x3=0;
		core::InputManager inputManager;

		core::gfx::Sprite blob;
		core::gfx::Sprite smog;
		core::gfx::Sprite screen; // the background.

		GUIButton resumeButton, optionButton, backButton, quitButton;
};

#endif
