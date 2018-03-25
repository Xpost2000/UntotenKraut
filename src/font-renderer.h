#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <ft2build.h>
#include <vector>
#include <map>
#include FT_FREETYPE_H

namespace core{
	namespace gfx{
		class FontRenderer{
			public:
				FontRenderer();
				~FontRenderer();
				void addFont( std::string path, std::string font_name );
				void setSize( int sz );
				void renderText( float x, float y, std::string text, std::string font_name, float r=1, float g=1, float b=1, float a=1 );
			private:
				int size=12;
				FT_Library m_ft;
				std::map<std::string, int> m_indices;
				std::vector<FT_Face>       m_faces;

				unsigned int vbo, vao;

				unsigned int textureId;
		};
	};
};

#endif
