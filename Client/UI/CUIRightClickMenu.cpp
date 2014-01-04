/* 
 * File:   CUIRightClickMenu.cpp
 * Author: karsten
 * 
 * Created on 1. marts 2012, 21:21
 */

#include "CUIRightClickMenu.h"

CUIRightClickMenu::CUIRightClickMenu(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight):
CUIButtonFrame(parrent,x,y,wight,hight){
	_mouseOk = true;
	
}



void CUIRightClickMenu::Draw(){
	int x ,y;
	SDL_GetMouseState(&x,&y);
	if(x>this->getX() && x <this->getX()+this->getWight() && y > this->getY() && y < this->getY() + this->getHight()){
		_mouseOk = true;

	}else{
		_mouseOk = false;
		_canBeRemoved = true;
	}
	Drawbox(this->getX(),this->getY(),this->getWight(),this->getHight(),0,0.2,0.1,1);
	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}
}

void CUIRightClickMenu::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"click CUIRightClickMenu"<<endl;
	cerr<<"x "<<x<<" y "<<y<<endl;
	this->_toBeDrawnFront = true;

	if(_MCbar && y < _MCbar->getHight()){
		cerr<<"click mc"<<endl;
		_MCbar->Click(event,x,y - _MCbar->getHight());
	}else{
		uint32_t qx = floor(_wight/_spreadX);
		for (map<uint32_t, CUIButton*>::iterator it = this->_buttons.begin(); it != this->_buttons.end(); it++){
			if (x >=  (it->first%qx) * this->_spreadX && x <= (((it->first%qx) * this->_spreadX)+it->second->getWight()) && y >=  floor(it->first / qx) * this->_spreadY && y <= ((floor(it->first / qx) * this->_spreadY)+it->second->getHight()) ){
				it->second->Click(event,x- it->second->getX() ,y- it->second->getY());
				this->_canBeRemoved = true;
				break;
			}
		}
	}
	cerr<<"done click CUIRightClickMenu"<<endl;
}


CUIRightClickMenu::~CUIRightClickMenu() {
}

