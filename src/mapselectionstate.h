#ifndef MAPSELECTION_STATE_H
#define MAPSELECTION_STATE_H
#include "state.h"
#include "input.h"
#include "sprite.h"
#include "gui_button.h"

class MapSelectionState : public State{
	public:
		MapSelectionState();
		~MapSelectionState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		float x1=0,x2=0,x3=0;
		core::InputManager inputManager;
		core::gfx::Sprite blob;
		core::gfx::Sprite smog;
		core::gfx::Sprite screen; // the background.

		GUIButton backButton;
};

#endif
