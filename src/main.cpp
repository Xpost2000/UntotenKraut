#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>

#include "window.h"
#include "sound.h"
#include "input.h"
#include "renderer.h"

#include "texturemanager.h"
#include "gunmanager.h"

#include "introstate.h"
#include "gamestate.h"
#include "menustate.h"
#include "pausestate.h"
#include "deathstate.h"
#include "optionmenustate.h"
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
	srand(time(NULL));

	window.Create( 
		       "Untoten Kraut"  ,
		       1024    ,
		       768 
		     );
	core::gfx::Renderer renderer(1024, 768);


	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_center.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_bottom_left.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_bottom_right.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_top_left.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_top_right.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_gun_buy.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_bars.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_center_blood.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//bunkergray//bunker_floor.png");

	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_bottom.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_bottom_ripped.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_center.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_left.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_right.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//ironcrossbanner//red_banner_top.png");

	core::TextureManager::getInstance()->loadTexture("assests//textures//nature//grass.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//nature//mud.png");

	core::TextureManager::getInstance()->loadTexture("assests//textures//props//crate.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//props//desk.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//props//desk_paper.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//props//desk_typewriter.png");
	core::TextureManager::getInstance()->loadTexture("assests//textures//props//oil_drum.png");

	core::audio::SoundManager::getInstance()->addSound("assests//sounds//hurt.wav", "hurt");
	core::audio::SoundManager::getInstance()->addSound("assests//sounds//hit.wav", "hit");
	core::audio::SoundManager::getInstance()->addSound("assests//sounds//uiclick.wav", "uiclick");
	core::audio::SoundManager::getInstance()->addSound("assests//sounds//bang.wav", "bang");

	rapidxml::xml_document<> gunDocument;
	rapidxml::xml_node<>* rootGunNode;

	std::ifstream gunsFile("assests//guns.xml");
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
		int cost = std::atoi(node->first_attribute("wallCost")->value());
		bool shotgun = std::atoi(node->first_attribute("shotgun")->value());

		game::GunManager::getInstance()->addGun(name, game::Gun(name, dmg, bulletSpeed, bulletLifeTime, delay, shotgun, maxAmmo, clipAmmo, reloadSpeed, cost));
	}

//	renderer.loadFont("assests//fonts//ocr.ttf",   "ocr");
	renderer.loadFont("assests//fonts//arial.ttf", "arial");
	renderer.loadFont("assests//fonts//tw.ttf", "typewriter");
	renderer.loadFont("assests//fonts//tw.ttf", "ocr");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	core::audio::SoundManager::getInstance()->addSound("assests//sounds//round_end.wav", "round_end");

	StateMachine stateMachine;
	GameState gameState;
	DeathState deathState;
	EditorState editorState;
	OptionMenuState optionState;
	MenuState menuState;
	IntroState introState;
	MapSelectionState mapSelectionState;
	PauseState pauseState;
	QuitState quitState;

	stateMachine.addState(&gameState, "game");
	stateMachine.addState(&introState, "intro");
	stateMachine.addState(&menuState, "menu");
	stateMachine.addState(&quitState, "quit");
	stateMachine.addState(&deathState, "death");
	stateMachine.addState(&editorState, "editor");
	stateMachine.addState(&optionState, "options");
	stateMachine.addState(&pauseState, "pause");
	stateMachine.addState(&mapSelectionState, "mapselect");
	stateMachine.setCurrentState("intro");

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
	stateMachine.data = &window;
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
