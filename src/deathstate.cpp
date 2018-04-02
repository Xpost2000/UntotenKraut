#include "fsm.h"
#include "deathstate.h"
#include "gamestate.h"

#include <iostream>

void DeathState::update(float dt){
	std::cout << "YOU ARE DEAD" << std::endl;
}

void DeathState::draw(core::gfx::Renderer& renderer){
	//TODO: Implement this.
	//Have a button that allows you to go back to the main menu basically.
}
