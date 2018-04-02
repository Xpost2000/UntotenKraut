#include "menustate.h"
#include "fsm.h"
#include <iostream>

MenuState::MenuState(){
	startButton = GUIButton( 0, 300, "Start Game", 20, 1, 1, 1, 1 );

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );
}

MenuState::~MenuState(){
}

void MenuState::update(float dt){
	SDL_SetRelativeMouseMode(SDL_FALSE);
	if(startButton.isClicked(inputManager))
		parent->setCurrentState("game");

	inputManager.Update();
}

void MenuState::draw(core::gfx::Renderer& renderer){
	renderer.identityCamera();
	startButton.draw(renderer);
}
