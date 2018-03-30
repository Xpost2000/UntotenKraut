#include "entity.h"
#include "bullet.h"

#include <vector>

namespace game{
	class Player : public Entity{
		public:
			Player( float x, float y, float w, float h, float speed, float hp );
			Player();
			~Player();

			void update(float dt);
			void draw(core::gfx::Renderer& renderer);

			void setSpeed( float s ) { speed=s; }
			void setHp( float h ) { hp=h; }

			float getSpeed() { return speed; }
			float getHp() { return hp; }

			void fire(float mX, float mY);
			
			std::vector<Bullet>& getBullets() { return bullets; }
		private:
			core::gfx::Sprite sprite;
			std::vector<Bullet> bullets;
			float speed=0;
			float hp=0;
	};
};
