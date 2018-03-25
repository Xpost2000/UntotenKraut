#ifndef SPRITE_H
#define SPRITE_H
#include <string>

#include "texture.h"

namespace core{
	namespace gfx{
		class Texture;
		class Sprite{
			public:
				Sprite( float x, float y, float w, float h, float angle=0.0f );
				~Sprite();
				float getX() { return x; }
				float getY() { return y; }
				float getW() { return w; }
				float getH() { return h; }
				float getAngle() { return angle; }
				Texture& getTexture() { return texture; }

				void setX( float nX ) { x = nX; }
				void setY( float nY ) { y = nY; }
				void setW( float nW ) { w = nW; }
				void setH( float nH ) { h = nH; }
				void setAngle( float nAngle ) { angle = nAngle; }
				void loadTexture( std::string path );
			private:
				float x, y, w, h;
				float angle;
				// until I make a texture class use that.
				Texture texture;
		};
	};
};

#endif
