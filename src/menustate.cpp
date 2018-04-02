#include "menustate.h"
#include "fsm.h"
#include <iostream>

MenuState::MenuState(){
}

MenuState::~MenuState(){
}

void MenuState::update(float dt){
	std::cout << "updating menu";
	parent->setCurrentState("game");
}

void MenuState::draw(core::gfx::Renderer& renderer){
	std::cout << "drawing menu";
}
