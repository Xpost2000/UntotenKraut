#ifndef INTRO_STATE_H
#define INTRO_STATE_H
#include "state.h"
#include "input.h"
class IntroState : public State{
	public:
		IntroState();
		~IntroState();
		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		std::string introMessage = "A Game By Xpost2000";
		std::string introDate    = "Made on April 30th 2018";

		int pointerX=150;
		int pointerY=300;

		float timer=1;
		float typeTimer=2;
		float blackInTimer=0;
		float blackOutTimer=20;

		core::InputManager inputManager;
};
#endif
