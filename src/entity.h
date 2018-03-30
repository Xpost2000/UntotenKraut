#ifndef ENTITY_H
#define ENTITY_H
#include "renderer.h"
namespace game{
	const int GENERIC_ENTITY=0;
	class World;
	class Entity{
		public:
			Entity( float x, float y, float w, float h );
			Entity();
			~Entity();
			virtual void update(float dt, World&);
			virtual void draw(core::gfx::Renderer&);
			bool touching(Entity& other);
			void setType( int t ) { type = t; }
			int getType(){ return type; }

			float x, y, w, h;
		private:
			int type=GENERIC_ENTITY;
	};
};
#endif
