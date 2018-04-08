#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

// I hope this monster works.
// going to test by just seeing if I get errors on compilation.

namespace core{
	namespace gfx{
		Shader::Shader(){
			vertex_shader = glCreateShader(GL_VERTEX_SHADER);
			fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);	
			shader_program = glCreateProgram();
		}

		Shader::~Shader(){
			glDeleteProgram(shader_program);
		}

		void Shader::loadFile( std::string vs_path, std::string fs_path ){
			std::fstream vs(vs_path);	
			std::fstream fs(fs_path);
			std::stringstream vs_str, fs_str;
			vs_str << vs.rdbuf();
			fs_str << fs.rdbuf();
			fs_src = fs_str.str();
			vs_src = vs_str.str();
			const char* vscstr = vs_src.c_str(), *fscstr = fs_src.c_str();
			glShaderSource(vertex_shader,   1, &vscstr, 0);
			glShaderSource(fragment_shader, 1, &fscstr, 0);
			glCompileShader(vertex_shader);
			char log[2048]; // since shaders aren't that big usually. There's less room for errors, so 2048 byte longs strings should be fine.

			glGetShaderInfoLog(vertex_shader, 2048, 0, log);

			glCompileShader(fragment_shader);
			glGetShaderInfoLog(fragment_shader, 2048, 0, log);

			glAttachShader(shader_program, fragment_shader);
			glAttachShader(shader_program, vertex_shader);

			glLinkProgram(shader_program);

			glDetachShader(shader_program, fragment_shader);
			glDetachShader(shader_program, vertex_shader);
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			glGetProgramInfoLog(shader_program, 2048, 0, log);
			std::cout << log << std::endl;
			std::cout << "Program log" << std::endl;
		}

		void Shader::loadMemory( std::string vs_str, std::string fs_str ){
			// probably swap
			// here.
			vs_src = vs_str;
			fs_src = fs_str;
			const char* vscstr = vs_src.c_str(), *fscstr = fs_src.c_str();
			char log[2048];
			glShaderSource(vertex_shader,   1, &vscstr, 0);
			glShaderSource(fragment_shader, 1, &fscstr, 0);

			glCompileShader(vertex_shader);
			glGetShaderInfoLog(vertex_shader, 2048, 0, log);

			glCompileShader(fragment_shader);
			glGetShaderInfoLog(fragment_shader, 2048, 0, log);

			glAttachShader(shader_program, fragment_shader);
			glAttachShader(shader_program, vertex_shader);

			glLinkProgram(shader_program);
			glGetProgramInfoLog(shader_program, 2048, 0, log);
			std::cout << log << std::endl;
			std::cout << "Program log" << std::endl;
		}

		int  Shader::getUniform( std::string name ){
			return glGetUniformLocation( shader_program, name.c_str() );
		}

		void Shader::uniformi( int location, int v0 ){
			glUseProgram(shader_program);
			glUniform1i(location, v0);
		}

		void Shader::uniformi( int location, int v0, int v1 ){
			glUseProgram(shader_program);
			glUniform2i(location, v0, v1);
		}
	
		void Shader::uniformi( int location, int v0, int v1, int v2 ){
			glUseProgram(shader_program);
			glUniform3i(location, v0, v1, v2);
		}

		void Shader::uniformi( int location, int v0, int v1, int v2, int v3 ){
			glUseProgram(shader_program);
			glUniform4i(location, v0, v1, v2, v3);
		}

		void Shader::uniformf( int location, float v0 ){
			glUseProgram(shader_program);
			glUniform1f(location, v0);
		}
	
		void Shader::uniformf( int location, float v0, float v1 ){
			glUseProgram(shader_program);
			glUniform2f(location, v0, v1);
		}

		void Shader::uniformf( int location, float v0, float v1, float v2 ){
			glUseProgram(shader_program);
			glUniform3f(location, v0, v1, v2);
		}

		void Shader::uniformf( int location, float v0, float v1, float v2, int v3 ){
			glUseProgram(shader_program);
			glUniform4f(location, v0, v1, v2, v3);
		}
	
		void Shader::uniformMatrix( int location, glm::mat4 mat ){
			glUseProgram(shader_program);
			glUniformMatrix4fv( location, 1, false, glm::value_ptr(mat) );
		}
		
		void Shader::useProgram(){
			glUseProgram(shader_program);
		}
	};
};
