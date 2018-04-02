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

		// TODO: Change m_texture to a shared_ptr
		/*
		void Sprite::loadTexture( std::string path ){
			if(!m_texture)
				m_texture = new Texture();
			m_texture->loadFile( path );
		}
		*/
	};
};
