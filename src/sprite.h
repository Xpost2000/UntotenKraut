#ifndef SPRITE_H
#define SPRITE_H

namespace core{
	namespace gfx{
		class Sprite{
			public:
				Sprite( float x, float y, float w, float h );
				~Sprite();
				float getX() { return x; }
				float getY() { return y; }
				float getW() { return w; }
				float getH() { return h; }
				int getTexture() { return texture; }

				void setX( float nX ) { x = nX; }
				void setY( float nY ) { y = nY; }
				void setW( float nW ) { w = nW; }
				void setH( float nH ) { h = nH; }
				void setTexture( int texId ) { texture = texId; }
			private:
				float x, y, w, h;
				// until I make a texture class use that.
				unsigned int texture;
		};
	};
};

#endif
