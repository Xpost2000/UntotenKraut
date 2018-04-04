#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "input.h"

#include "wall.h"
#include "player.h"
#include "world.h"
#include "gui_text.h"

#include "state.h"
#include "sprite.h"

#include "gunmanager.h"

#include "levelloader.h"

class GameState : public State{
	public:
		GameState();
		~GameState();

		void update(float dt);
		void draw(core::gfx::Renderer&);

		void loadLevel(std::string levelFile, std::string name);
	private:
		friend class DeathState;
		friend class EditorState;
		core::gfx::Sprite uiBloodStain;
		core::gfx::Sprite gunUi;
		game::LevelLoader levelLoader;

		float roundDelay=20;
		int gameWave=0;
		core::InputManager inputManager;

		bool isPlayerReloading=false;
		bool canRepairBarricade=false;
		bool canBuyWallGun=false;
		float playerBuildDelay=0;
		float playerBuyDelay=0;
		int currentGunPrice=0;

		glm::vec2 inWorld;

		game::Player player;
		game::World  world;

		GUIText scoreText;
		GUIText weaponText;
};

#endif
