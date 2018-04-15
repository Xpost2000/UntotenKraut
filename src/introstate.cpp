#include "introstate.h"
#include <iostream>
#include "fsm.h"

IntroState::IntroState(){
}

IntroState::~IntroState(){
}

void IntroState::update(float dt){
	if(timer>0){
		timer-=dt;
		std::cout << timer << std::endl;
	}else{
		if(blackOutTimer>0){
			blackOutTimer-=dt;
		}		
		else if(blackInTimer<40){
			blackInTimer+=dt;
		}else{
			parent->setCurrentState("menu");
		}
	}
	if(inputManager.isKeyDown(SDL_SCANCODE_RETURN)){
			parent->setCurrentState("menu");
	}
	inputManager.Update();
}

void IntroState::draw(core::gfx::Renderer& renderer){
	renderer.setTextSize(50);
	renderer.drawText("typewriter", pointerX, pointerY, introMessage);
	renderer.drawText("typewriter", pointerX, pointerY+60, introDate);
	if(blackOutTimer>=0){
		renderer.drawRect(0, 0, renderer.getScreenWidth(), renderer.getScreenHeight(), 0, 0, 0, blackOutTimer/10);
	}else if(blackInTimer>=0){
		renderer.drawRect(0, 0, renderer.getScreenWidth(), renderer.getScreenHeight(), 0, 0, 0, (blackInTimer/10));
	}
}
