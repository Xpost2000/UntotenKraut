#include "gamestate.h"
#include "fsm.h"
#include <iostream>

GameState::GameState(){
}

GameState::~GameState(){
}

void GameState::update(float dt){
	std::cout << "updating game" << std::endl;
	parent->setCurrentState("menu");
}

void GameState::draw(core::gfx::Renderer&){
	std::cout << "Drawing game" << std::endl;
}
