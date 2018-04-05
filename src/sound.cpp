#include "sound.h"
#include <iostream>

namespace core{
	namespace audio{
		std::shared_ptr<SoundManager> SoundManager::instance;
		SoundManager::SoundManager(){

		}
		SoundManager::~SoundManager(){
		}
		// You have to manually deconstruct this since 
		// if I declare this on the stack like all my other variables.
		// It dies whenever the main function finishes. But SDL_Mixer quits
		// before the end of the main function so these functions below would do nothing.
		void SoundManager::free(){
			stopMusic();
			stopSound(-1);
			for(auto& music : m_musics){
				Mix_FreeMusic(music.second);
			}
			for(auto& chunk : m_chunks){
				Mix_FreeChunk(chunk.second);
			}
		}
		
		void SoundManager::addSound ( std::string path  , std::string sound ){
			Mix_Chunk* temporary_copy = Mix_LoadWAV( path.c_str() );
			m_chunks.emplace( std::make_pair(sound, temporary_copy) );
		}

		void SoundManager::addMusic ( std::string path  , std::string music ){
			Mix_Music* temporary_copy = Mix_LoadMUS( path.c_str() );
			std::cerr << Mix_GetError() << std::endl;
			m_musics.emplace( std::make_pair(music, temporary_copy) );

		}

		void SoundManager::playSound( std::string sound , int channel , int volume, int loops ){
			Mix_Volume(channel, volume);
			Mix_PlayChannel(channel, m_chunks[sound], loops);
		}

		void SoundManager::playMusic( std::string music , int volume, int loop ){
			Mix_VolumeMusic(volume);
			if(!Mix_PlayingMusic()){
				Mix_PlayMusic(m_musics[music], loop);
				std::cerr << Mix_GetError() << std::endl;
			}
		}

		void SoundManager::stopMusic(){
			Mix_HaltMusic();
		}

		void SoundManager::stopSound( int channel ){
			Mix_HaltChannel(channel);
		}
	};
};
