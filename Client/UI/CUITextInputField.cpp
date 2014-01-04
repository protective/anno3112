/* 
 * File:   CUITextInputField.cpp
 * Author: karsten
 * 
 * Created on 2. marts 2012, 21:16
 */

#include "CUITextInputField.h"

CUITextInputField::CUITextInputField(CUIBaseFrame* parrent,uint32_t x, uint32_t y, uint32_t wight, uint32_t hight):
CUIFrame(parrent){
	_x = x;
	_y = y;
	_wight = wight;
	_hight = hight;
	_pos = 0;
	_textField = "";
	_deltaBlink = 0;
	
}


void CUITextInputField::Click(SDL_Event event,int32_t x, int32_t y){
	//if (x >= this->x && x <= this->x+this->wight && y >= this->y && y <= this->y+this->hight){
		cerr<<"click CUITextInputField"<<endl;

	//}
		_pos = _textField.length();
		focusFrame = this;
}

void CUITextInputField::KeyDown(SDL_Event event){
	cerr<<"keydown"<<endl;
	if(focusFrame == this){
		char ch = *SDL_GetKeyName(event.key.keysym.sym);

		if(event.key.keysym.sym>= 32 && event.key.keysym.sym <= 125){
			_textField.insert(_pos,1,ch);
			_pos++;
		}

		if(event.key.keysym.sym == 276 && _pos > 0)
			_pos--;
		if(event.key.keysym.sym == 275 && _pos < _textField.length())
			_pos++;
		if(event.key.keysym.sym == 8 && _pos > 0){
			_pos--;
			_textField.erase(_pos,1);
			
		}
		if(event.key.keysym.sym == 13)
			focusFrame = NULL;
	}
}

void CUITextInputField::Draw(){

	Drawbox(_x+_parrent->getX(),_y+_parrent->getY(),_wight,_hight,0.1,0.1,0.1,1);

	glLoadIdentity();
	font.FaceSize(16);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
	stringstream s;
	
	if(focusFrame == this)
		s<<_textField.substr(0,_pos)<<"|"<<_textField.substr(_pos);
	else
		s<<_textField;
	font.Render(s.str().c_str());


}


CUITextInputField::~CUITextInputField() {
}

