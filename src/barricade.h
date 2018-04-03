#ifndef BARRICADE_H
#define BARRICADE_H

#include "entity.h"
#include "sprite.h"

namespace game{
	class Barricade : public Entity{
		public:
			Barricade( float x, float y, float w, float h );
			void update(float dt, World&){}
			void draw(core::gfx::Renderer&);
			void setHealth(float hp){ health=hp; }
			const float getHealth() { return health; }
		private:
			core::gfx::Sprite sprites[2];
			float health=100;
	};
};
#endif
