/* 
 * File:   CUIComboBox.cpp
 * Author: karsten
 * 
 * Created on 9. oktober 2011, 10:12
 */

#include "CUIComboBox.h"



CUIComboBox::CUIComboBox(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight) :
CUIFrame(parrent){
	_UIlevel = 3;
	this->_x = x;
	this->_y = y;
	this->_wight = wight;
	this->_hight = hight;
	_spreadY = 14;
	_active = false;
}

void CUIComboBox::Draw(){

	if (_active){
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY*(1+_frames.size()),0.4,0.1,0.1,1);
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			(*it)->Draw();
		}
	}else{
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY,0.4,0.1,0.1,1);
	}
}

void CUIComboBox::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"click CUIComboBox"<<endl;
	cerr<<"x "<<x<<" y "<<y<<endl;
	this->_toBeDrawnFront = true;

	if(_MCbar && y < _MCbar->getHight()){
		cerr<<"click cbmcbar"<<endl;
		_MCbar->Click(event, x,y - _MCbar->getHight());
	}else if((_MCbar && y < _MCbar->getHight() + 14) || (!_MCbar && y < 14)){
		cerr<<"click mc open"<<endl;
		this->_active =!this->_active;
	}else if (_active){
		for (map<uint32_t, CUIButton*>::iterator it = this->_buttons.begin(); it != this->_buttons.end(); it++){	
			if (x >=  0 && x <= it->second->getWight() && y >= (it->first * this->_spreadY)+ 14 && y <= (it->first * this->_spreadY)+it->second->getHight()+14){
				it->second->Click(event,x- it->second->getX() ,y- it->second->getY());
				_active = false;
			}
		}
	}
	
	cerr<<"done click CUIComboBox"<<endl;
}

void CUIComboBox::AddButton(CUIButton& button, uint32_t pos){
	uint32_t exray = 14;
	if(this->getMCbar()){
		exray += this->getMCbar()->getHight();
	}
	while (true){
		if (this->_buttons.find(pos) == this->_buttons.end()){
			this->_buttons[pos] = &button;
			
			button.SetX(5);
			button.SetY(exray+(pos*_spreadY));
			button.setWight(this->_wight);
			button.setHight(_spreadY);
			this->add(button);
			cerr<<"addbutton"<<endl;
			break;
		}else{
			pos+=1;
		}
	}
}

void CUIComboBox::AddButton(CUIButton& button){
	uint32_t pos = 0;
	while (true){
		if (this->_buttons.find(pos) == this->_buttons.end()){
			this->AddButton(button, pos);
			break;
		}else{
			pos+=1;
		}
	}
}

void CUIComboBox::RemoveButton(uint32_t pos){
	delete this->_buttons[pos];
	this->remove(*this->_buttons[pos]);
	this->_buttons.erase(pos);
}

CUIComboBox::~CUIComboBox() {
	for(map<uint32_t,CUIButton*>::iterator it = this->_buttons.begin(); it != this->_buttons.end(); it++){
		if (it->second)
			delete it->second;
	}
}

