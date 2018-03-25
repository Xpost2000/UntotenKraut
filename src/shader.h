#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>

namespace core{
	// This class loads shaders.
	class Shader{
		public:
			// going to make it two part construction
			// so you can either load from a binary.
			// a source code file
			// or directly from memory.
			Shader();
			~Shader();

			void loadFile( std::string vs_path, std::string fs_path );
			void loadMemory( std::string vs_str, std::string fs_str );

			int  getUniform( std::string name );

			// here's a slew of uniform setters.
			// (only i and f because those are the only 2 data types I'd probably use)
			// I could probably template this... But it's safer to just overload.
			void uniformi( int location, int v0 );
			void uniformi( int location, int v0, int v1 );
			void uniformi( int location, int v0, int v1, int v2 );
			void uniformi( int location, int v0, int v1, int v2, int v3 );
			void uniformf( int location, float v0 );
			void uniformf( int location, float v0, float v1 );
			void uniformf( int location, float v0, float v1, float v2 );
			void uniformf( int location, float v0, float v1, float v2, int v3 );

			void uniformMatrix( int location, glm::mat4 mat );

			void useProgram();

		private:
			unsigned int vertex_shader, fragment_shader, shader_program;
			std::string vs_src;
			std::string fs_src;
	};
};

#endif
