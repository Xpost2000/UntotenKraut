#include "fsm.h"
#include "state.h"

StateMachine::StateMachine(){
}

StateMachine::~StateMachine(){
}

void StateMachine::addState(State* newState, std::string name){
	newState->parent = this;
	states.insert(std::make_pair(name, newState));
}

void StateMachine::update(float dt){
	currentState->update(dt);
}

void StateMachine::draw(core::gfx::Renderer& renderer){
	currentState->draw(renderer);
}

void StateMachine::setCurrentState(std::string name){
	if(states.count(name))
	currentState = states[name];
}
