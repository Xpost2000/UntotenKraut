#ifndef GUNMANAGER_H
#define GUNMANAGER_H

#include <unordered_map>
#include <memory>

#include "gun.h"

namespace game{
	class GunManager{
		public:
			GunManager();
			GunManager(const GunManager& other)=delete;
			~GunManager();
			static std::shared_ptr<GunManager> getInstance(){
				if(!instance){
					instance = std::shared_ptr<GunManager>{new GunManager};
				}
				return instance;
			}
			void addGun(std::string name, Gun gun);

			Gun get(std::string name);
		private:
			static std::shared_ptr<GunManager> instance;
			std::unordered_map<std::string, Gun> guns;
	};
};
#endif
