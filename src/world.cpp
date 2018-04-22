#include "world.h"
#include <algorithm>

namespace game{
	void World::draw(core::gfx::Renderer& renderer){
		Entity cameraRect(-renderer.camX, -renderer.camY, 1024, 768);
		for(auto& detail : detail_ents){
			if(detail.touching(cameraRect))
			detail.draw(renderer);
		}
		for(auto& bar : barricades){
			if(bar.touching(cameraRect))
			bar.draw(renderer);
		}
		for(auto& zombie : zombies){
			if(zombie.touching(cameraRect))
			zombie.draw(renderer);
		}
		for(auto& wall : walls){
			if(wall.touching(cameraRect))
			wall.draw(renderer);
		}
		for(auto& bullet : player->getBullets()){
			if(bullet.touching(cameraRect))
			bullet.draw(renderer);
		}
		player->draw(renderer);
	//	renderer.drawRect(-renderer.camX/*-(1024/6)*/, -renderer.camY/*-(768/6)*/, 1024, 768, 0, 1, 0, 0.5);
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
				// 10 more steps
				for(int i = 0; i < 10; ++i){
					zombie.getPs().update(0.1f);
				}
				zombie.cleared=true;
				score+=50;
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
