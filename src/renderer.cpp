#include "renderer.h"
#include <iostream>

namespace core{
	Renderer::Renderer( int w, int h ){
		projection = glm::ortho<float>(
				0.f, (float)w,
				(float)h, 0.f,
				-1.f, 1000.f
			     );
		glGenBuffers(1, &vbo);
		glGenVertexArrays(1, &vao);
		// I could "orphan it first." but I'll do it later. This is easier
		// let's setup the vertex attributes first.
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*8, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*2));
		glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*4));
		texture_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\textured.fs");
		default_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\default.fs");
		text_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\text.fs");
		default_shader.uniformMatrix(default_shader.getUniform("projection"), projection);
		default_shader.uniformMatrix(default_shader.getUniform("view"), view);
		texture_shader.uniformMatrix(texture_shader.getUniform("projection"), projection);
		texture_shader.uniformMatrix(texture_shader.getUniform("view"), view);
	}

	Renderer::~Renderer(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void Renderer::drawRect( float x, float y, float w, float h, float r, float g, float b, float a ){
		float data[]= {
			x, y,       0, 1,  r, g, b, a,
			x, y+h,     1, 0,  r, g, b, a,
			x+w, y,     0, 1,  r, g, b, a,
			x+w, y,     0, 1,  r, g, b, a,
			x, y+h,     1, 0,  r, g, b, a,
			x+w, y+h,   1, 1,  r, g, b, a
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindVertexArray(vao);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof data,
				data,
				GL_DYNAMIC_DRAW
			    );
		default_shader.useProgram();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Renderer::setResolution( int w, int h ){
		projection = glm::ortho<float>(
			0.f, (float)w,
			(float)h, 0.f,
			-1.f, 1000.f
		);
	}

	void Renderer::drawRectTextured( int texture, float x, float y, float w, float h, float r, float g, float b, float a ){
		float data[]= {
			x, y,       0, 1,  r, g, b, a,
			x, y+h,     1, 0,  r, g, b, a,
			x+w, y,     0, 1,  r, g, b, a,
			x+w, y,     0, 1,  r, g, b, a,
			x, y+h,     1, 0,  r, g, b, a,
			x+w, y+h,   1, 1,  r, g, b, a
		};

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindVertexArray(vao);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof data,
				data,
				GL_DYNAMIC_DRAW
			    );
		glActiveTexture(GL_TEXTURE0);
		glBindTexture( GL_TEXTURE_2D, texture );
		texture_shader.useProgram();
		texture_shader.uniformi(texture_shader.getUniform("texture"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Renderer::refreshCamera(){
		default_shader.uniformMatrix(default_shader.getUniform("view"), view);
		texture_shader.uniformMatrix(texture_shader.getUniform("view"), view);
	}

	void Renderer::drawText( std::string text, float scaleX, float scaleY, float r, float g, float b, float a ){
	}	
};
