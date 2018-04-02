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

class GameState : public State{
	public:
		GameState();
		~GameState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		friend class DeathState;
		core::gfx::Sprite uiBloodStain;

		float roundDelay=20;
		int gameWave=0;
		core::InputManager inputManager;

		bool isPlayerReloading=false;
		game::Player player;
		game::World  world;

		GUIText scoreText;
		GUIText weaponText;
};

#endif
