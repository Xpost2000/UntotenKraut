#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "renderer.h"

namespace core{
	namespace gfx{
		struct Particle{
			float x=0, y=0;
			float w=1, h=1;
			float r=1,g=1,b=1,a=1;
			float lifeTime=-1;
		};
		// this is VERY game specific.
		// If I were making a better particle system.
		// It would just be more customizable.
		// But since I'm only using this for one effect.
		// this is excusable
		class ParticleSystem{
			public:
				ParticleSystem();
				ParticleSystem(float x, float y, int size=15);
				~ParticleSystem();

				void setAttributes( float speedX, float speedY, float angle );
				void resetPositions();

				void update(float dt);
				void draw(Renderer&);

				float x=0;
				float y=0;
				float angle=0;
				bool active=false;
				float speedX=25;
				float speedY=15;
			private:

				int size=15;
				int getDeadParticle();
				std::vector<Particle> pool;
		};
	};
};

#endif
