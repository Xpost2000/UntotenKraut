#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
namespace core{
	namespace gfx{
		class Texture{
			public:
				Texture();
				Texture( std::string path );
				Texture( int width, int height, unsigned char* bytes );

				~Texture();
				void loadMemory( int width, int height, unsigned char* bytes );
				void loadFile( std::string path );

				void setFilters( int magFilter, int minFilter );
				void setWrapping( int sWrap, int tWrap );
				void use();
				void unuse();

				unsigned int getId();
				std::string path;
			private:
				unsigned int id;
		};
	};
};

#endif
