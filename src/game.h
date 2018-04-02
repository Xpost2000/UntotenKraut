#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "sound.h"
#include "input.h"
#include "shader.h"
#include "renderer.h"
#include "sprite.h"

#include "world.h"

#include "wall.h"
#include "player.h"

#include "texturemanager.h"
#include "gunmanager.h"

class Game{
	public:
		Game();
		~Game();
		void run(float dt);
		bool shouldRun() { return running; }
	private:
		void draw();
		void update(float dt);
};
#endif
