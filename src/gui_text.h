#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include <string>

#include "renderer.h"

class GUIText{
	public:
		GUIText(){}
		GUIText( float x, float y, std::string text, float textSz );
		~GUIText();
		void setBoxColor(float r, float g, float b, float a);
		void setTextColor(float r, float g, float b, float a);
		void setText(std::string text, float sz=12);
		void setPosition(float x, float y);

		void draw(core::gfx::Renderer& renderer);
	private:
		friend class GUIButton;
		float x,  y;
		float w,  h;
		float textSize=12;
		std::string text="text";	

		float tr=0,tg=0,tb=0,ta=1;
		float r=1, g=1, b=1, a=1;
};
#endif
