#include "pausestate.h"
#include "sound.h"
#include "texturemanager.h"
#include "fsm.h"
#include "gamestate.h"

PauseState::PauseState(){

	screen = core::gfx::Sprite(0, 0, 1024, 768);
	blob = core::gfx::Sprite(0, 0, 0, 0);
	smog = core::gfx::Sprite(0, 0, 1024, 768);

	resumeButton = GUIButton( 15, 300, "Resume Game", 20, 1, 1, 1, 1 );
	optionButton = GUIButton( 15, 330, "Options Menu", 20, 1, 1, 1, 1 );
	backButton = GUIButton( 15, 360, "Quit To Menu", 20, 1, 1, 1, 1 );
	quitButton = GUIButton( 15, 390, "Quit To Windows", 20, 1, 1, 1, 1 );

	smog.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//smog.png"));
	blob.setTexture(core::TextureManager::getInstance()->getTexture("assests//ui//ui_blob.png"));

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );
}

PauseState::~PauseState(){
}

void PauseState::update(float dt){
	SDL_SetRelativeMouseMode(SDL_FALSE);
	if(resumeButton.isClicked(inputManager)){
		parent->setCurrentState("game");
	}
	if(optionButton.isClicked(inputManager)){
		parent->setCurrentState("options");
	}
	if(backButton.isClicked(inputManager)){
		core::audio::SoundManager::getInstance()->stopMusic();
		parent->setCurrentState("menu");
	}
	if(quitButton.isClicked(inputManager)){
		parent->setCurrentState("quit");
	}

	x1+=15*dt;
	x2+=30*dt;
	x3+=7*dt;

	inputManager.Update();
}

void PauseState::draw(core::gfx::Renderer& renderer){
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
	renderer.drawText("ocr", 0, 0, "Pause Menu");
	renderer.setTextSize(15);
	renderer.drawText("ocr", 0, 65, "Take a break. You might need it.");
	GameState* ptr = (GameState*)parent->getState("game");
	renderer.setTextSize(25);
	renderer.drawText("ocr", 450, 100, "Round : " + std::to_string(ptr->gameWave) , 1, 0, 0, 1);
	renderer.drawText("ocr", 450, 130, "Game Score : " + std::to_string(ptr->world.getScore()) , 1, 0, 0, 1);
	smog.setX(0);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	smog.setX(x1);
	renderer.drawSprite(smog, 1, 1, 1, 0.1);
	smog.setX(x2);
	renderer.drawSprite(smog, 0.5, 0.4, 0.5, 0.2);
	smog.setX(x3);
	renderer.drawSprite(smog, 1, 1, 1, 0.2);
	resumeButton.draw(renderer, &blob);
	optionButton.draw(renderer, &blob);
	backButton.draw(renderer, &blob);
	quitButton.draw(renderer, &blob);
}
