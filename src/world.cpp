#include "world.h"

namespace game{
	void World::draw(core::gfx::Renderer& renderer){
		for(auto& wall : walls){
			wall.draw(renderer);
		}
		for(auto& zombie : zombies){
			zombie.draw(renderer);
		}
		for(auto& bullet : player->getBullets()){
			bullet.draw(renderer);
		}
		player->draw(renderer);
	}

	void World::update(float dt){
		for(auto& zombie : zombies){
			zombie.update(0.1f, *this);
		}
		for(int i = 0; i < player->getBullets().size(); ++i){
			player->getBullets()[i].update( 0.1f, *this );
			if(!player->getBullets()[i].isAlive()){
				player->getBullets().erase(player->getBullets().begin()+i);
			}

		}
		player->update(0.1f, *this);
	}
};
