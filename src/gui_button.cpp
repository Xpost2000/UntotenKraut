#include "gui_button.h"
#include "sound.h"
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
		if(held==true){
			text_gui.r = hr-0.3;	
			text_gui.g = hg-0.3;	
			text_gui.b = hb-0.3;	
			text_gui.a = ha;
		}
		if(held==false){
			if(input.isMouseKeyDown(SDL_BUTTON_LEFT)){
				held=true;
				// should probably separate into two sounds.
				return false;
			}
		}else{
			if(!input.isMouseKeyDown(SDL_BUTTON_LEFT)
			 && (input.GetMouseX() < text_gui.x + text_gui.w && input.GetMouseX()+1 > text_gui.x)
	    && (input.GetMouseY() < text_gui.y + text_gui.h && input.GetMouseY()+1 > text_gui.y) ){
				held=false;
				core::audio::SoundManager::getInstance()->playSound("uiclick", 3);
				return true;
			}
		}
	}else{
		text_gui.r = r;	
		text_gui.g = g;	
		text_gui.b = b;	
		text_gui.a = a;	
	}
	//held=false;
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
