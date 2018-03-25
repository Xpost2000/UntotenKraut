#include <GL/glew.h>

#include <SDL2/SDL_image.h>

#include "texture.h"

namespace core{
	namespace gfx{
		Texture::Texture(){
			glGenTextures(1, &id);
			use();
			setWrapping(GL_REPEAT, GL_REPEAT);
			setFilters(GL_NEAREST, GL_NEAREST);
		}	
	
		Texture::Texture( std::string path ) : Texture(){
			loadFile(path);
		}

		Texture::Texture( int width, int height, unsigned char* bytes ) : Texture(){
			loadMemory(width, height, bytes);
		}

		Texture::~Texture(){
			glDeleteTextures(1, &id);
		}

		void Texture::setFilters( int magFilter, int minFilter ){
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
		}

		void Texture::setWrapping( int sWrap, int tWrap ){
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap );
		}

		void Texture::loadFile( std::string path ){
			use();
			SDL_Surface* temp = IMG_Load(path.c_str());
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, temp->w, temp->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
			SDL_FreeSurface(temp);
		}
		
		void Texture::loadMemory( int width, int height, unsigned char* bytes ){
			use();
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes );

		}

		void Texture::use(){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Texture::unuse(){
			glBindTexture(GL_TEXTURE_2D, 0);

		}

		unsigned int Texture::getId(){
			return id;
		}
	};
};
