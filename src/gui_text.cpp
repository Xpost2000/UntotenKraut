#include "gui_text.h"

GUIText::GUIText( float x, float y, std::string text, float textSz ) : x(x), y(y), text(text), textSize(textSz){
	w = textSz*text.size();
	h = textSz+5;
}

GUIText::~GUIText(){
}

void GUIText::setBoxColor(float r, float g, float b, float a){
	this->r=r;
	this->g=g;
	this->b=b;
	this->a=a;
}

void GUIText::setTextColor(float r, float g, float b, float a){
	this->tr=r;
	this->tg=g;
	this->tb=b;
	this->ta=a;
}

void GUIText::setText(std::string text, float sz){
	this->text=text;
	textSize=sz;
	w=sz*text.size(); // width and height to fit box
	h=sz;
}

void GUIText::setPosition(float x, float y){
	this->x=x;
	this->y=y;
}

void GUIText::draw(core::gfx::Renderer& renderer){
	renderer.drawRect(x, y, w, h, r, g, b, a);
	renderer.setTextSize(textSize);
	renderer.drawText("arial", x, y, text, tr, tg, tb, ta);
}
