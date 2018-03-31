#include "world.h"

namespace game{
	void World::draw(core::gfx::Renderer& renderer){
		for(auto& wall : walls){
			wall.draw(renderer);
		}
		for(auto& zombie : zombies){
			zombie.draw(renderer);
			renderer.drawText( "arial", zombie.x, zombie.y, "HP: " + std::to_string(zombie.getHp()), 1, 1, 1, 1);
		}
		for(auto& bullet : player->getBullets()){
			bullet.draw(renderer);
		}
		player->draw(renderer);
	}

	void World::update(float dt){
		for(int i = 0; i < zombies.size(); ++i){
			auto& zombie = zombies[i];
			zombie.update(0.1f, *this);
			if(zombie.getHp() <= 0){
				zombies.erase(zombies.begin()+i);
			}
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
