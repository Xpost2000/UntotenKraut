#include "sprite.h"

// this isn't ment to be finished yet.
// just a placeholder.
namespace core{
	namespace gfx{
		Sprite::Sprite( float x, float y, float w, float h, float angle )
		: x(x), y(y), w(w), h(h), angle(angle){
		}

		Sprite::~Sprite(){
		}

		void Sprite::loadTexture( std::string path ){
			texture.loadFile( path );
		}
	};
};
