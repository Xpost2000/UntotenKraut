#include "gamestate.h"
#include "fsm.h"
#include "sound.h"
#include "texturemanager.h"
#include <iostream>

GameState::GameState(){
	player = game::Player(0, 0, 30, 30, 15, 100);

	uiBloodStain = core::gfx::Sprite( 0, 0, 0, 0, 0 );
	uiBloodStain.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\ui_stain.png"));
	gunUi = core::gfx::Sprite(900, 650, 90, 45);

	player.setGuns(game::GunManager::getInstance()->get("M1911A1"), game::Gun());
	player.useGun(0);
	
	world.setPlayer(&player);
	// this is for the test world. In the future I will load maps from files instead.
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
}

GameState::~GameState(){
}

void GameState::loadLevel(std::string fileName, std::string name){
	levelLoader.loadNew(fileName, name);
	world.loadLevel(levelLoader.getLevel(name));
	player.setHp(100);
	roundDelay=43;
	gameWave=0;
	player.setGuns(game::GunManager::getInstance()->get("M1911A1"), game::Gun());
	player.useGun(0);
}

void GameState::update(float dt){
	if(playerBuildDelay > 0){
		playerBuildDelay-=dt;
	}
	if(playerBuyDelay > 0){
		playerBuyDelay-=dt;
	}
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
		roundDelay=43;
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
	canRepairBarricade=false;
	for(auto& barricade : world.getBarricades()){
		if(player.touching(barricade.getTrigger())&&barricade.getHealth() < 100){
			canRepairBarricade=true;
			if( inputManager.isKeyDown(SDL_SCANCODE_F) ){
				if(playerBuildDelay <= 0){
					barricade.setHealth(barricade.getHealth()+25);
					world.getScore()+=25;
					playerBuildDelay=5;
				}
			}
			break;
		}
	}
	canBuyWallGun=false;
	currentGunPrice=0;
	for(auto& wall : world.getWalls()){
		if(wall.getHasGun()){
			if(player.touching(wall.getTrigger())){
				canBuyWallGun=true;
				currentGunPrice=wall.getCost();
			if( inputManager.isKeyDown(SDL_SCANCODE_F) ){
				if(playerBuyDelay <= 0 && world.getScore()>=wall.getCost()){
					world.getScore()-=currentGunPrice;
					//TODO: do more advanced checking.
					if(player.getGuns()[1].getName() == "Nothing"){
						player.getGuns()[1] = wall.getWallWeapon();
						player.useGun(1);
					}else{
						player.getGun() = wall.getWallWeapon();
					}
					playerBuyDelay=5;
				}
			}
			break;
			}
		}
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
		player.fire(inWorld.x, inWorld.y);
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
			player.fire(inWorld.x, inWorld.y);
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
	world.draw(renderer);
	inWorld = renderer.mouseToWorld(inputManager.GetMouseX(), inputManager.GetMouseY());
	renderer.drawRect(inWorld.x, inWorld.y, 5, 5, 1, 0, 0, 1);
	renderer.identityCamera();
	renderer.refreshCamera();
	renderer.drawRect(0,0,renderer.getScreenWidth(), renderer.getScreenHeight(), 0, 0, 0, 0.65);

	//artificially "darken" the world without a postprocessor.

	// Rendering the hud is down here.

	renderer.identityCamera();
	renderer.refreshCamera();
	if(canRepairBarricade){
		renderer.setTextSize(30);
		renderer.drawText("ocr", 1024/2-200, 768/2, "Press F to Repair Barricade", 0.8, 0.8, 0, 1);
	}
	if(canBuyWallGun){
		renderer.setTextSize(30);
		renderer.drawText("ocr", 1024/2-200, 768/2, "Press F to Buy Gun(" + std::to_string(currentGunPrice)+")", 0.8, 0.8, 0, 1);
	}

	gunUi.setTexture(core::TextureManager::getInstance()->getTexture("assests\\ui\\"+player.getGun().getName()+"_hud.png"));
	scoreText.setText("Score: "+ std::to_string(world.getScore()), 14);
	weaponText.setText(player.getGun().getName()+": " + std::to_string(player.getGun().getCurrentCapacity()) + "/" + std::to_string(player.getGun().getMaxCapacity()), 14);
	renderer.drawSprite(gunUi);
	scoreText.draw(renderer, &uiBloodStain);
	weaponText.draw(renderer, &uiBloodStain);

	renderer.setTextSize(100);
	renderer.drawText("ocr",0,660, std::to_string(gameWave), 1, 0, 0, 1);	
	if(world.getMaxZombies() == world.getKillCount()){
		renderer.setTextSize(20);
		renderer.drawText("ocr",0,580, "Preparation Time.", 1, 0, 0, 1);	
	}
}
