#include "gamestate.h"
#include "fsm.h"
#include <iostream>

GameState::GameState(){
	player = game::Player(0, 0, 30, 30, 15, 100);
	player.getGun() = game::GunManager::getInstance()->get("M1911A1");
	
	world.setPlayer(&player);
	world.addWall(game::Wall( 100, 200, 60, 60 ));
	world.addWall(game::Wall( 100, 500, 60, 60 ));

	world.addSpawner(300, 200, 30, 5);
	world.addSpawner(600, 200, 30, 5);
	world.addSpawner(800, 500, 30, 5);

	weaponText = GUIText(900, 720, "", 15);
	scoreText =  GUIText(900, 700, "", 15);

	weaponText.setBoxColor(1, 1, 1, 1);
	weaponText.setTextColor(0, 0, 0, 1);
	scoreText.setBoxColor(1, 0, 0, 1);
	scoreText.setTextColor(1, 1, 1, 1);
}

GameState::~GameState(){
}

void GameState::update(float dt){
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
		player.getGun() = game::GunManager::getInstance()->get("M1911A1");
	}
	if( inputManager.isKeyDown( SDL_SCANCODE_2 ) ){
		player.getGun() = game::GunManager::getInstance()->get("M4A1");
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
			player.move(0.1f, 1, world);

		}else if ( inputManager.GetJoystickState().left_vertical < 128 ){
			player.move(0.1f, 2, world);
		}

		if( inputManager.GetJoystickState().left_horizontal > 128 ){
			player.move(0.1f, 3, world);
		}else if ( inputManager.GetJoystickState().left_horizontal < 128 ){
			player.move(0.1f, 4, world);
		}

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

	scoreText.setText("Score: "+ std::to_string(world.getScore()));
	weaponText.setText(player.getGun().getName()+": " + std::to_string(player.getGun().getCurrentCapacity()) + "/" + std::to_string(player.getGun().getMaxCapacity()));
	scoreText.draw(renderer);
	weaponText.draw(renderer);
	renderer.setTextSize(33);
	renderer.drawText("ocr",0,700, std::to_string(gameWave), 1, 0, 0, 1);	
	if(world.getMaxZombies() == world.getKillCount()){
		renderer.setTextSize(20);
		renderer.drawText("ocr",0,680, "Preparation Time.", 1, 0, 0, 1);	
	}
	renderer.refreshCamera();
	world.draw(renderer);
}
