#ifndef WALL_H
#define WALL_H

#include "entity.h"
#include "sprite.h"

namespace game{
	class Wall : public Entity{
		public:
			Wall( float x, float y, float w, float h );
			void update(float dt, World&);
			void draw(core::gfx::Renderer&);
			int getType() { return type; }
		private:	
			int type=0;
	};
};

#endif
