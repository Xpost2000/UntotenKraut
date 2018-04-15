#ifndef SPRITE_H
#define SPRITE_H
#include <string>

#include "texture.h"

namespace core{
	namespace gfx{
		class Texture;
		class Sprite{
			public:
				Sprite(){}
				Sprite( float x, float y, float w, float h, float angle=0.0f );
				~Sprite();
				float getX() { return m_x; }
				float getY() { return m_y; }
				float getW() { return m_w; }
				float getH() { return m_h; }
				float getAngle() { return m_angle; }
				Texture* getTexture() { return m_texture; }

				void setX( float nX ) { m_x = nX; }
				void setY( float nY ) { m_y = nY; }
				void setW( float nW ) { m_w = nW; }
				void setH( float nH ) { m_h = nH; }
				void setAngle( float nAngle ) { m_angle = nAngle; }
//				void loadTexture( std::string path );
				void setTexture( Texture *tex ) { m_texture = tex; }
				core::gfx::Texture* getTex() { return m_texture; }
			private:
				float m_x, m_y, m_w, m_h;
				float m_angle;
				// until I make a texture class use that.
				Texture* m_texture;
		};
	};
};

#endif
