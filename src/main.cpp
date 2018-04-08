#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <fstream>
#include <vector>
#include <iostream>

#include "window.h"
#include "sound.h"
#include "input.h"
#include "renderer.h"

#include "texturemanager.h"
#include "gunmanager.h"

#include "gamestate.h"
#include "menustate.h"
#include "deathstate.h"
#include "editorstate.h"
#include "quitstate.h"
#include "mapselectionstate.h"
#include "fsm.h"

#include "dep/rapidxml.hpp"

extern "C"{
	void _atExit(void){
		printf("Freeing sdl resources...\n");
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();	
	}
}

int main( int argc, char** argv ){
	atexit(_atExit);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	Mix_Init(MIX_INIT_MP3);
	core::Window window;
	core::InputManager inputManager;

	window.Create( 
		       "Untoten Kraut"  ,
		       1024    ,
		       768 
		     );
	core::gfx::Renderer renderer(1024, 768);
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_512_tset.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_barricade_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_wallbuy_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_projectile.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_player_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\ui\\ui_stain.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\dev_zombie_test.png");
	core::TextureManager::getInstance()->loadTexture("assests\\textures\\test_ground.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_cl.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_cr.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_clb.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\mud_crb.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\mud.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\floor.png");
	core::TextureManager::getInstance()->getTexture("assests\\textures\\concrete.png");

	rapidxml::xml_document<> gunDocument;
	rapidxml::xml_node<>* rootGunNode;

	std::ifstream gunsFile("assests\\guns.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(gunsFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	gunDocument.parse<0>(&buffer[0]);
	rootGunNode = gunDocument.first_node("GunsDocument");
	for(auto* node = rootGunNode->first_node("Gun"); node; node=node->next_sibling("Gun")){
		std::string name = node->first_attribute("name")->value();
		int dmg = std::atoi(node->first_attribute("dmg")->value());
		int bulletSpeed = std::atoi(node->first_attribute("bulletSpeed")->value());
		int bulletLifeTime = std::atoi(node->first_attribute("bulletLifeTime")->value());
		float delay = std::stof(node->first_attribute("delay")->value());
		int maxAmmo = std::atoi(node->first_attribute("maxAmmo")->value());
		int clipAmmo = std::atoi(node->first_attribute("clipAmmo")->value());
		float reloadSpeed = std::stof(node->first_attribute("reloadSpeed")->value());

		game::GunManager::getInstance()->addGun(name, game::Gun(name, dmg, bulletSpeed, bulletLifeTime, delay, false, maxAmmo, clipAmmo, reloadSpeed ));
	}

	renderer.loadFont("assests\\fonts\\ocr.ttf",   "ocr");
	renderer.loadFont("assests\\fonts\\arial.ttf", "arial");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	core::audio::SoundManager::getInstance()->addSound("assests\\sounds\\round_end.wav", "round_end");

	StateMachine stateMachine;
	GameState gameState;
	DeathState deathState;
	EditorState editorState;
	MenuState menuState;
	MapSelectionState mapSelectionState;
	QuitState quitState;

	stateMachine.addState(&gameState, "game");
	stateMachine.addState(&menuState, "menu");
	stateMachine.addState(&quitState, "quit");
	stateMachine.addState(&deathState, "death");
	stateMachine.addState(&editorState, "editor");
	stateMachine.addState(&mapSelectionState, "mapselect");
	stateMachine.setCurrentState("menu");

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				stateMachine.setCurrentState("quit");
			}
	 );

	Uint32 start = 0;
	Uint32 last  = 0;
	Uint32 difference=0;
	const float preferredDt=0.1f;
	float actualDt=0.1f;
	while( stateMachine.getCurrentState() != &quitState ){
		start = SDL_GetTicks();
		difference = start - last;
		last = start;
		actualDt= std::min(difference/100.0f, preferredDt);
		stateMachine.update(actualDt);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		stateMachine.draw(renderer);
		inputManager.Update();
		window.Refresh();
		
	}
	SDL_SetRelativeMouseMode(SDL_FALSE);
	core::audio::SoundManager::getInstance()->free();	
	core::TextureManager::getInstance()     ->free();
	return 0;
}
