#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <vector>
#include <memory> // for the std::shared_ptr
#include <string>

#include "texture.h"

namespace core{
	class TextureManager{
		public:
			TextureManager()=default;
			TextureManager(const TextureManager& other) = delete;
			TextureManager& operator=(const TextureManager& other) = delete;
			~TextureManager();

			static std::shared_ptr<TextureManager> getInstance(){
				if(!instance) { 
					instance = std::shared_ptr<TextureManager>{new TextureManager};
			       	}
				return instance;
			}

			// this will cache the texture
			// the identifier will be the path for once.
			gfx::Texture* loadTexture( std::string path );
			gfx::Texture* getTexture ( std::string path );
			void free();

			// this looks as confusing as it looks.
			std::vector<std::pair<std::string, gfx::Texture*>> getTextures(){
				return textureVecMap;
			}
		private:
			// I'm actually using std::shared_ptr for the right reason.
			static std::shared_ptr<TextureManager> instance;
			std::vector<std::pair<std::string, gfx::Texture*>> textureVecMap;
			std::unordered_map<std::string, gfx::Texture*> textures;
	};
};

#endif
