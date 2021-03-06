#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>

#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "font-renderer.h"
// in the future I should make it more robust
// but for now it serves to be very basic.
// just enough to carry me through a prototyping stage.
namespace core{
	namespace gfx{
		class Sprite;
		class Renderer{
			public:
				Renderer( int w, int h );
				~Renderer();
	
				void drawRect( float x, float y, float w, float h, float r =1, float g =1, float b =1, float a =1, bool wireFrame=false );
				void drawRectTextured( int texture, float x, float y, float w, float h, float r =1, float g =1, float b =1, float a =1 );
				void drawSprite( Sprite& spr, float r=1, float g=1, float b=1, float a=1 );		
				void setResolution( int w, int h );

				void refreshCamera();
				void scaleCamera( float x, float y );
				void centerCameraOn( float x, float y );
				void identityCamera();

				void loadFont( std::string path, std::string name );
				void drawText( std::string font_name, float x, float y, std::string text, float r=1, float g=1, float b=1, float a=1 );
				void setTextSize( int sz ){ fontRenderer.setSize(sz); }
				float getScreenWidth() { return scrW; }
				float getScreenHeight() { return scrH; }
				void translateCamera(float x, float y);
				glm::vec2 mouseToWorld(float x, float y);
				float camX=0, camY=0;
				float scaleX=1, scaleY=1;
			private:
				int scrW=0, scrH=0;
				Shader texture_shader, default_shader, text_shader;
				//TODO: ADD TEXTURE MANAGER
				FontRenderer fontRenderer;
				unsigned int vbo, vao;
	
				glm::mat4 projection=glm::mat4(), view=glm::mat4(), model=glm::mat4();
		};
	};
};

#endif
