#include "renderer.h"
#include <iostream>

#include "sprite.h"

namespace core{
	namespace gfx{
		Renderer::Renderer( int w, int h ){
			projection = glm::ortho<float>(
					0.f, (float)w,
					(float)h, 0.f,
					-1.f, 1000.f
				     );
			scrW=w;
			scrH=h;
			glGenBuffers(1, &vbo);
			glGenVertexArrays(1, &vao);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*8, 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*2));
			glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*4));

			/*
			 * If I had taken more time to write an optimized renderer.
			 * I'm certainly OpenGL allows this I could just make a shader manager
			 * and cache the files loaded and reuse the objects instead of generating new objects.
			 */
			texture_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\textured.fs");
			default_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\default.fs");
			text_shader.loadFile("assests\\shaders\\default.vs", "assests\\shaders\\text.fs");

			default_shader.uniformMatrix(default_shader.getUniform("projection"), projection);
			default_shader.uniformMatrix(default_shader.getUniform("view"), view);

			texture_shader.uniformMatrix(texture_shader.getUniform("projection"), projection);
			texture_shader.uniformMatrix(texture_shader.getUniform("view"), view);

			text_shader.uniformMatrix(text_shader.getUniform("projection"), projection);
			text_shader.uniformMatrix(text_shader.getUniform("view"), view);
		}

		Renderer::~Renderer(){
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}
	
		void Renderer::drawRect( float x, float y, float w, float h, float r, float g, float b, float a, bool wireFrame ){
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
			glBufferData( GL_ARRAY_BUFFER, sizeof data, data, GL_DYNAMIC_DRAW );
			default_shader.useProgram();
			if(wireFrame){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
			}else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		void Renderer::setResolution( int w, int h ){
			projection = glm::ortho<float>(
				0.f, (float)w,
				(float)h, 0.f,
				-1.f, 1000.f
			);
			scrW=w;
			scrH=h;
		}
	
		void Renderer::drawRectTextured( int texture, float x, float y, float w, float h, float r, float g, float b, float a ){
			float data[]= {
				x, y,       0, 0,  r, g, b, a,
				x, y+h,     0, 1,  r, g, b, a,
				x+w, y,     1, 0,  r, g, b, a,
				x+w, y,     1, 0,  r, g, b, a,
				x, y+h,     0, 1,  r, g, b, a,
				x+w, y+h,   1, 1,  r, g, b, a
			};
	
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindVertexArray(vao);
			glBufferData( GL_ARRAY_BUFFER, sizeof data, data, GL_DYNAMIC_DRAW );
			glActiveTexture(GL_TEXTURE0);
			glBindTexture( GL_TEXTURE_2D, texture );
			texture_shader.useProgram();
			texture_shader.uniformi(texture_shader.getUniform("texture"), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		
		void Renderer::drawSprite( Sprite& spr, float r, float g, float b, float a ){
			float x = spr.getX();
			float y = spr.getY();
			float w = spr.getW();
			float h = spr.getH();
			float data[]= {
				x, y,       0, 0,  r, g, b, a,
				x, y+h,     0, 1,  r, g, b, a,
				x+w, y,     1, 0,  r, g, b, a,
				x+w, y,     1, 0,  r, g, b, a,
				x, y+h,     0, 1,  r, g, b, a,
				x+w, y+h,   1, 1,  r, g, b, a
			};
	
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindVertexArray(vao);
			// rechange to bufferdata. Orphaning doesn't work cause I did something wrong.
			glBufferSubData(
					GL_ARRAY_BUFFER,
					0, sizeof(data),
					data
			);
			glActiveTexture(GL_TEXTURE0);
			texture_shader.useProgram();
			texture_shader.uniformi(texture_shader.getUniform("texture"), 0);
			spr.getTexture()->use();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	
		void Renderer::refreshCamera(){
			default_shader.uniformMatrix(default_shader.getUniform("view"), view);
			texture_shader.uniformMatrix(texture_shader.getUniform("view"), view);
		}

		void Renderer::loadFont( std::string path, std::string name ){
			fontRenderer.addFont(path, name);
		}

		void Renderer::drawText( std::string font_name, float x, float y, std::string text, float r, float g, float b, float a ){
			text_shader.useProgram();
			fontRenderer.renderText( x, y, text, font_name, r, g, b, a );
			glBindTexture(GL_TEXTURE_2D, 0);
		}	

		void Renderer::identityCamera(){
			view = glm::mat4();
		}

		void Renderer::translateCamera(float x, float y){
			identityCamera();
			camX+=x;
			camY+=y;
			view = glm::translate(view, glm::vec3(camX, camY, 0.0f));
		}

		void Renderer::scaleCamera(float x, float y){
			scaleX=x;
			scaleY=y;
			view = glm::scale(view, glm::vec3(x, y, 0.0f));
		}

		glm::vec2 Renderer::mouseToWorld(float x, float y){
			// thank god for glm's convience functions
			glm::vec2 result = glm::unProject(glm::vec3(glm::vec2(x,scrH-y), 0.0f), view, projection, glm::vec4(0, 0, scrW, scrH));
			return result;
		}

		void Renderer::centerCameraOn(float x, float y){
			camX = -x + (scrW/2.0f);
			camY = -y + (scrH/2.0f);
			view = glm::translate(view, glm::vec3(camX, camY, 0.0f));
		}
	};
};
