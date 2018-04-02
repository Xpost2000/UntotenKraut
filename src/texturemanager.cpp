#include "texturemanager.h"
#include <iostream>

namespace core{
	std::shared_ptr<TextureManager> TextureManager::instance=nullptr;
	//TODO: Debug a crash that is somehow happening here...
	TextureManager::~TextureManager(){
	}

	void TextureManager::free(){
		for(auto& texture : textures){
			if(texture.second){
				delete texture.second;
			}
		}
	}

	gfx::Texture* TextureManager::loadTexture( std::string path ){
		if(textures.count(path)) { 
			return textures[path];
	       	}else{
			gfx::Texture* newTexture = new gfx::Texture( path );
			textures.insert(std::make_pair(path, newTexture));
			return newTexture;
		}
	}

	gfx::Texture* TextureManager::getTexture( std::string path ){
		if(textures.count(path)){
			return textures[path];
		}else{
			return loadTexture( path );
		}
	}
};
