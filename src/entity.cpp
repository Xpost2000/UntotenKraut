#include "entity.h"

namespace game{
	Entity::Entity( float x, float y, float w, float h )
	: x(x), y(y), w(w), h(h){

	}
	
	Entity::Entity(){

	}

	Entity::~Entity(){

	}

	void Entity::update(float dt, World& world){

	}

	void Entity::draw(core::gfx::Renderer&){

	}

	bool Entity::touching(Entity& other){
		return( x < other.x + other.w && x+w > other.x )
			&&
		      ( y < other.y + other.h && y+h > other.y );
	}
};
