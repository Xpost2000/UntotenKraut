#include "optionmenustate.h"
#include "window.h"

#include "fsm.h"
#include "gamestate.h"
#include "texturemanager.h"
#include "sound.h"
#include <iostream>

OptionMenuState::OptionMenuState(){
	blob = core::gfx::Sprite(0,0,0,0);
	smog = core::gfx::Sprite(0, 0, 0, 0);
	smog.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//smog.png"));
	blob.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//ui_blob.png"));
	fullscreenButton = GUIButton( 15, 300, "Toggle Fullscreen", 20, 1, 1, 1, 1 );
	vsyncButton = GUIButton( 15, 325, "Toggle VSync", 20, 1, 1, 1, 1 );
	backButton = GUIButton( 15, 700, "Return to Menu", 20, 1, 1, 1, 1 );

	core::audio::SoundManager::getInstance()->addMusic( "assests//sounds//packupyourtroubles.mp3", "menu" );

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );

}

OptionMenuState::~OptionMenuState(){
}

void OptionMenuState::update(float dt){
	SDL_SetRelativeMouseMode(SDL_FALSE);
	core::audio::SoundManager::getInstance()->playMusic( "menu", 100, true );

	core::Window* ptr = (core::Window*)parent->data;
	if(fullscreenButton.isClicked(inputManager)){
		if(!fs){
			SDL_SetWindowFullscreen(ptr->GetHandle(), SDL_WINDOW_FULLSCREEN);
		}else{
			SDL_SetWindowFullscreen(ptr->GetHandle(), 0);
			SDL_SetWindowPosition(ptr->GetHandle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			SDL_SetWindowSize(ptr->GetHandle(), 1024, 768);
		}
		fs = !fs;
	}
	if(vsyncButton.isClicked(inputManager)){
		ptr->getSwapInterval() ^= 1;
		SDL_GL_SetSwapInterval(ptr->getSwapInterval());
	}
	if(backButton.isClicked(inputManager)){
		core::audio::SoundManager::getInstance()->stopMusic();
		GameState* ptr = (GameState*)parent->getState("game");	
		if(ptr->gameHasBegun){
			parent->setCurrentState("pause");
		}else{
			parent->setCurrentState("menu");
		}
	}
	

	x1+=15*dt;
	x2+=30*dt;
	x3+=7*dt;

	inputManager.Update();
}

void OptionMenuState::draw(core::gfx::Renderer& renderer){
	screen = core::gfx::Sprite(0, 0, renderer.getScreenWidth(), renderer.getScreenHeight());
	screen.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//menu.png"));
	renderer.identityCamera();
	renderer.refreshCamera();
	smog.setW(renderer.getScreenWidth());
	smog.setH(renderer.getScreenHeight());

	if(x1 > renderer.getScreenWidth()){
		x1=0;
	}if(x2 > renderer.getScreenWidth()){
		x2=0;
	}if(x3 > renderer.getScreenWidth()){
		x3=0;
	}
	
	// I could make a particle engine for this but eh.

	renderer.drawRect(0,0,0,0);
	renderer.drawSprite(screen);
	renderer.setTextSize(60);
	renderer.drawText("ocr", 0, 0, "Options Menu");
	renderer.setTextSize(15);
	renderer.drawText("ocr", 0, 65, "TODO: Add Resolution Selection. (While I'm at it, add uniform scaling that doesn't break the gui)");
	smog.setX(0);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	smog.setX(x1);
	renderer.drawSprite(smog, 1, 1, 1, 0.1);
	smog.setX(x2);
	renderer.drawSprite(smog, 0.5, 0.4, 0.5, 0.2);
	smog.setX(x3);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	core::Window* ptr = (core::Window*)parent->data;
	fullscreenButton.getText().setText("Toggle Fullscreen : " + std::string(((fs) ? "ON" : "OFF")), 20);
	vsyncButton.getText().setText("Toggle VSync(Toggle at own risk): " + std::string(((ptr->getSwapInterval() == 1) ? "ON" : "OFF")), 20);
	fullscreenButton.draw(renderer, &blob);
	vsyncButton.draw(renderer, &blob);
	backButton.draw(renderer, &blob);
}
