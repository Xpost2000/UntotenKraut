#include "gui_button.h"
#include <iostream>

GUIButton::GUIButton( float x, float y, std::string text, float textSz, float r, float g, float b, float a )
: text_gui( GUIText(x, y, text, textSz) ), r(r), g(g), b(b), a(a){
	text_gui.r=r;
	text_gui.g=g;
	text_gui.b=b;
	text_gui.a=a;

}

bool GUIButton::isClicked(core::InputManager& input){
	if( (input.GetMouseX() < text_gui.x + text_gui.w && input.GetMouseX()+1 > text_gui.x)
	    && (input.GetMouseY() < text_gui.y + text_gui.h && input.GetMouseY()+1 > text_gui.y) ){
		text_gui.r = hr;	
		text_gui.g = hg;	
		text_gui.b = hb;	
		text_gui.a = ha;	
		if(input.isMouseKeyDown(SDL_BUTTON_LEFT)){
			return true;
		}
	}else{
		text_gui.r = r;	
		text_gui.g = g;	
		text_gui.b = b;	
		text_gui.a = a;	
	}
	return false;
}

bool GUIButton::isMousedOver(core::InputManager& input){
	if( (input.GetMouseX() < text_gui.x + text_gui.w && input.GetMouseX()+1 > text_gui.x)
	    && (input.GetMouseY() < text_gui.y + text_gui.h && input.GetMouseY()+1 > text_gui.y) ){		
		text_gui.r = hr;	
		text_gui.g = hg;	
		text_gui.b = hb;	
		text_gui.a = ha;	
		return true;
	}else{
		text_gui.r = r;	
		text_gui.g = g;	
		text_gui.b = b;	
		text_gui.a = a;	
		return false;
	}
}

void GUIButton::draw(core::gfx::Renderer& renderer, core::gfx::Sprite* useSprite){
	text_gui.draw(renderer, useSprite);
}
