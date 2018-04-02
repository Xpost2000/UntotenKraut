#include "fsm.h"
#include "deathstate.h"
#include "gamestate.h"

#include <iostream>

void DeathState::update(float dt){
	countDown-=dt*2;
	if(countDown<=0){
		countDown=100;
		parent->setCurrentState("menu");
	}
}

void DeathState::draw(core::gfx::Renderer& renderer){
	//TODO: Implement this.
	//Have a button that allows you to go back to the main menu basically.
	renderer.identityCamera();
	GameState* gs = (GameState*)parent->getState("game");
	renderer.setTextSize(40);
	renderer.drawText("ocr", 0, 0, "You tried champ.", countDown/100.0f, countDown/100.0f, countDown/100.0f, countDown/100.0f);
	renderer.drawText("ocr", 0, 45, "Your final score: " + std::to_string(gs->world.getScore()), countDown/100.0f, countDown/100.0f, countDown/100.0f, countDown/100.0f);
	renderer.drawText("ocr", 0, 90, "You made it to Round " + std::to_string(gs->gameWave), countDown/100.0f, countDown/100.0f, countDown/100.0f, countDown/100.0f);
}
