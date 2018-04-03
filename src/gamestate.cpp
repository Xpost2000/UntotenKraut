#include "gamestate.h"
#include "fsm.h"
#include "sound.h"
#include "texturemanager.h"
#include <iostream>

GameState::GameState(){
	player = game::Player(0, 0, 30, 30, 15, 100);

	ground = core::gfx::Sprite(-500, -500, 2000, 2000);
	ground.setTexture(core::TextureManager::getInstance()->getTexture("assests\\textures\\test_ground.png"));
	uiBloodStain = core::gfx::Sprite( 0, 0, 0, 0, 0 );
	uiBloodStain.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\ui_stain.png"));
	gunUi = core::gfx::Sprite(900, 650, 90, 45);

	player.setGuns(game::GunManager::getInstance()->get("M1911A1"), game::GunManager::getInstance()->get("M4A1"));
	player.useGun(0);
	
	world.setPlayer(&player);
	// this is for the test world. In the future I will load maps from files instead.
	world.addWall(game::Wall( 100, 200, 60, 60 ));
	world.addWall(game::Wall( 100, 500, 60, 60 ));
	world.addBarricade(game::Barricade(300, 300, 30, 30));
	world.addBarricade(game::Barricade(300, 600, 30, 30));

	world.addSpawner(300, 200, 10, 5);
	world.addSpawner(600, 200, 10, 5);
	world.addSpawner(800, 500, 10, 5);

	weaponText = GUIText(900, 720, "", 15);
	scoreText =  GUIText(900, 700, "", 15);

	weaponText.setBoxColor(1, 0, 1, 1);
	weaponText.setTextColor(1, 1, 1, 1);
	scoreText.setBoxColor(1, 0, 0, 1);
	scoreText.setTextColor(1, 1, 1, 1);

	inputManager.AddCallback(
			SDL_QUIT,
			[&](SDL_Event& evnt){
				parent->setCurrentState("quit");
			}
	 );
	levelLoader.load("maps\\test.txt", "test");
	world.loadLevel(levelLoader.getLevel("test"));
}

GameState::~GameState(){
}

void GameState::update(float dt){
	if(player.getHp()<=0){
		parent->setCurrentState("death");
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if(world.getMaxZombies() == world.getKillCount()){
		roundDelay-=dt;
	}
	if(roundDelay<=0){
		gameWave++;
		world.nextWave();
		world.getKillCount()=0;
		roundDelay=20;
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_W ) ){
		player.move(0.1f, 1, world);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_S ) ){
		player.move(0.1f, 2, world);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_A ) ){
		player.move(0.1f, 3, world);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_D ) ){
		player.move(0.1f, 4, world);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_1 ) ){
		player.useGun(0);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_2 ) ){
		player.useGun(1);
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_R ) ){
		isPlayerReloading=true;
	}
	if(isPlayerReloading){
		isPlayerReloading=!player.getGun().reload(0.1f);
	}

	if( inputManager.isMouseKeyDown( SDL_BUTTON_LEFT ) ){
		if(!isPlayerReloading)
		player.fire(inputManager.GetMouseX(), inputManager.GetMouseY());
	}
	if(inputManager.CheckForController()){
		if( inputManager.GetJoystickState().left_vertical > 128 ){
			player.move(0.1f, 3, world);

		}else if ( inputManager.GetJoystickState().left_vertical < 128 ){
			player.move(0.1f, 4, world);
		}

		if( inputManager.GetJoystickState().left_horizontal > 128 ){
			player.move(0.1f, 1, world);
		}else if ( inputManager.GetJoystickState().left_horizontal < 128 ){
			player.move(0.1f, 2, world);
		}
		std::cout << "Joystick value (LEFT HORIZONTAL): ";
		std::cout << inputManager.GetJoystickState().left_horizontal << std::endl;
		std::cout << "Joystick value (LEFT VERTICAL): ";
		std::cout << inputManager.GetJoystickState().left_vertical << std::endl;

		if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_X ) ){
			isPlayerReloading=true;
		}
		if( inputManager.isButtonDown( SDL_CONTROLLER_BUTTON_RIGHTSHOULDER ) ){
			if(!isPlayerReloading)
			player.fire(inputManager.GetMouseX(), inputManager.GetMouseY());
		}
	}
	if( inputManager.isKeyDown(SDL_SCANCODE_ESCAPE) )
		parent->setCurrentState("menu");

	inputManager.Update();
	world.update(dt);
}

void GameState::draw(core::gfx::Renderer& renderer){
	renderer.centerCameraOn(player.x, player.y);
	renderer.refreshCamera();
	renderer.drawSprite(ground);
	world.draw(renderer);

	// Rendering the hud is down here.

	renderer.identityCamera();

	gunUi.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\"+player.getGun().getName()+"_hud.png"));
	scoreText.setText("Score: "+ std::to_string(world.getScore()), 14);
	weaponText.setText(player.getGun().getName()+": " + std::to_string(player.getGun().getCurrentCapacity()) + "/" + std::to_string(player.getGun().getMaxCapacity()), 14);
	renderer.drawSprite(gunUi);
	scoreText.draw(renderer, &uiBloodStain);
	weaponText.draw(renderer, &uiBloodStain);

	renderer.setTextSize(45);
	renderer.drawText("ocr",0,700, std::to_string(gameWave), 1, 0, 0, 1);	
	if(world.getMaxZombies() == world.getKillCount()){
		renderer.setTextSize(20);
		renderer.drawText("ocr",0,680, "Preparation Time.", 1, 0, 0, 1);	
	}
}
