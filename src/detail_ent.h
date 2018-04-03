#ifndef DETAIL_ENT_H
#define DETAIL_ENT_H
#include "entity.h"
#include "sprite.h"
namespace game{
	class DetailEntity : public Entity{
		public:
			DetailEntity(float x, float y, float w, float h, core::gfx::Texture*);
			~DetailEntity();
			void draw(core::gfx::Renderer&);
		private:
			core::gfx::Sprite spr;
	};
};
#endif
