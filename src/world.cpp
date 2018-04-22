#include "world.h"
#include <algorithm>

namespace game{
	void World::draw(core::gfx::Renderer& renderer){
		for(auto& detail : detail_ents){
			detail.draw(renderer);
		}
		for(auto& bar : barricades){
			bar.draw(renderer);
		}
		for(auto& zombie : zombies){
			zombie.draw(renderer);
		}
		for(auto& wall : walls){
			wall.draw(renderer);
		}
		for(auto& bullet : player->getBullets()){
			bullet.draw(renderer);
		}
		player->draw(renderer);
	}

	void World::update(float dt){
		for(auto& spawner : zombieSpawners){
			if(spawner.isActive())
			spawner.update(dt);
		}
		for(int i = 0; i < zombies.size(); ++i){
			auto& zombie = zombies[i];
			if(zombie.getHp()> 0 && zombie.cleared == false){
				zombie.update(0.1f, *this);
			}
			else if(zombie.getHp() <= 0 && zombie.cleared==false){
				killCount++;
				zombie.cleared=true;
				score+=150;
			}
			/*
			if(zombie.getHp()<= 0 && zombie.doneBleeding()){
				zombies.erase(zombies.begin()+i);
			}
			*/
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
