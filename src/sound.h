#ifndef SOUND_H
#define SOUND_H
/*
 * This isn't for a class named Sound which somewhat
 * breaks my previous conventions.
 *
 * But it's really for a sound manager.
 */

#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <vector>
#include <memory>

namespace core{
	namespace audio{
		class SoundManager{
			public:
				SoundManager();
				~SoundManager();
				void addSound ( std::string path , std::string sound );
				void addMusic ( std::string path , std::string music );
				void playSound( std::string sound , int channel , int volume=100, int loops=0);
				void playMusic( std::string music , int volume=100, int loop=false);
				void stopMusic();
				void stopSound(int channel=-1);

				static std::shared_ptr<SoundManager> getInstance(){
					if(!instance){
						instance = std::shared_ptr<SoundManager>{ new SoundManager };
					}
					return instance;
				}
			private:
				void free();
				static std::shared_ptr<SoundManager> instance;
				std::unordered_map<std::string, Mix_Chunk*> m_chunks;
				std::unordered_map<std::string, Mix_Music*> m_musics;
		};
	};
};

#endif
