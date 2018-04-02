#include "texturemanager.h"
#include <iostream>

namespace core{
	std::shared_ptr<TextureManager> TextureManager::instance=nullptr;
	TextureManager::~TextureManager(){
		//I'm printing here because I need to make sure std::shared_ptr does what it should be doing
		std::cout << "Freeing resources..." << std::endl;	
		//TODO: Implement
		for(auto& texture : textures){
			if(texture.second){
				delete texture.second;
			}
		}
	}

	gfx::Texture* TextureManager::loadTexture( std::string path ){
		if(textures.count(path)) { 
			std::cout << "Valid texture found." << std::endl;
			return textures[path];
	       	}else{
			std::cout << "Loading texture." << std::endl;
			gfx::Texture* newTexture = new gfx::Texture( path );
			textures.insert(std::make_pair(path, newTexture));
			return newTexture;
		}
	}

	gfx::Texture* TextureManager::getTexture( std::string path ){
		if(textures.count(path)){
			std::cout << "Valid texture found." << std::endl;
			return textures[path];
		}else{
			return loadTexture( path );
		}
	}
};
