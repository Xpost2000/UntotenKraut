#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H
#include "gui_text.h"
#include "input.h"

class GUIButton{
	public:
		GUIButton(){}
		GUIButton( float x, float y, std::string text, float textSz, float r, float g, float b, float a );
		GUIText& getText() {
		       	return text_gui; 
		}

		bool isClicked(core::InputManager& input);
		bool isMousedOver(core::InputManager& input);

		void draw(core::gfx::Renderer& renderer, core::gfx::Sprite* useSprite=nullptr);
	private:
		bool held=false;
		GUIText text_gui;
		
		float hr=0,hg=0.5,hb=0.5,ha=1;
		float r=1, g=1, b=1, a=1;
};

#endif
