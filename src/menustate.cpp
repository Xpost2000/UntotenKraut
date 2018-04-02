#include "menustate.h"
#include "fsm.h"
#include <iostream>

MenuState::MenuState(){
	startButton = GUIButton( 0, 300, "Start Game", 20, 1, 1, 1, 1 );
}

MenuState::~MenuState(){
}

void MenuState::update(float dt){
	if(startButton.isClicked(inputManager))
		parent->setCurrentState("game");

	inputManager.Update();
}

void MenuState::draw(core::gfx::Renderer& renderer){
	startButton.draw(renderer);
}
