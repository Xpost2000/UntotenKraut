#include "menustate.h"

#include "fsm.h"
#include "texturemanager.h"
#include "sound.h"
#include <iostream>

MenuState::MenuState(){
	blob = core::gfx::Sprite(0,0,0,0);
	smog = core::gfx::Sprite(0, 0, 0, 0);
	smog.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//smog.png"));
	blob.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//ui_blob.png"));
	startButton = GUIButton( 15, 300, "Start Game", 20, 1, 1, 1, 1 );
	optionButton = GUIButton( 15, 330, "Options", 20, 1, 1, 1, 1 );
	editModeButton = GUIButton( 15, 360, "Editor Mode", 20, 1, 1, 1, 1 );
	quitButton = GUIButton( 15, 390, "Quit Game", 20, 1, 1, 1, 1 );

	core::audio::SoundManager::getInstance()->addMusic( "assests//sounds//packupyourtroubles.mp3", "menu" );

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
	core::audio::SoundManager::getInstance()->playMusic( "menu", 100, true );

	if(startButton.isClicked(inputManager)){
		// TODO: Add another menu sub state ( the map selection screen )
		parent->setCurrentState("mapselect");
	}
	if(optionButton.isClicked(inputManager)){
		parent->setCurrentState("options");
	}
	if(editModeButton.isClicked(inputManager)){
		core::audio::SoundManager::getInstance()->stopMusic();
		parent->setCurrentState("editor");
	}
	if(quitButton.isClicked(inputManager)){
		core::audio::SoundManager::getInstance()->stopMusic();
		parent->setCurrentState("quit");
	}
	

	x1+=15*dt;
	x2+=30*dt;
	x3+=7*dt;

	inputManager.Update();
}

void MenuState::draw(core::gfx::Renderer& renderer){
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
	renderer.drawText("ocr", 0, 0, "Untoten Kraut");
	renderer.setTextSize(15);
	renderer.drawText("ocr", 0, 65, "Welcome to Version 0.80");
	smog.setX(0);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	smog.setX(x1);
	renderer.drawSprite(smog, 1, 1, 1, 0.1);
	smog.setX(x2);
	renderer.drawSprite(smog, 0.5, 0.4, 0.5, 0.2);
	smog.setX(x3);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	startButton.draw(renderer, &blob);
	optionButton.draw(renderer, &blob);
	editModeButton.draw(renderer, &blob);
	quitButton.draw(renderer, &blob);
}
