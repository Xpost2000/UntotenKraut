#include "sprite.h"

// this isn't ment to be finished yet.
// just a placeholder.
namespace core{
	namespace gfx{
		Sprite::Sprite( float x, float y, float w, float h, float angle )
		: m_x(x), m_y(y), m_w(w), m_h(h), m_angle(angle){
		}

		Sprite::~Sprite(){
		}

		void Sprite::loadTexture( std::string path ){
			m_texture.loadFile( path );
		}
	};
};
