/* 
 * File:   CUIComboOrdreChange.cpp
 * Author: karsten
 * 
 * Created on 14. januar 2012, 00:40
 */

#include "CUIComboOrdreChange.h"
#include "../Buttons/CUIButtonChangeOrdre.h"
#include "../../spaceobjects/CShip.h"
CUIComboOrdreChange::CUIComboOrdreChange(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight):
CUIComboBox(parrent,x,y,wight,hight){
	cerr<<"first"<<endl;
	for(map<uint32_t,COrdres*>::iterator it = globalOrders.begin(); it != globalOrders.end(); it++){
		cerr<<"reset add"<<endl;
		this->AddButton(*(new CUIButtonChangeOrdre(this,it->second)));
	}

}


void CUIComboOrdreChange::Draw(){
	if (_active){
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY*(1+_frames.size()),0.4,0.1,0.1,1);
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			(*it)->Draw();
		}
	}else{
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY,0.4,0.1,0.1,1);
	}
	if (playerSels){
		if (playerSels->isShip()){
			if(playerSels->isShip()->getOrdres()){
				glLoadIdentity();
				font.FaceSize(16);
				glColor3f(1.0, 1.0, 1.0);
				glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
				stringstream s;
				s<<playerSels->isShip()->getOrdres()->getName();
				font.Render(s.str().c_str());

			}
		}
	}
}

void CUIComboOrdreChange::Click(SDL_Event event, int32_t x, int32_t y){
	cerr<<"click CUIComboOrdreChange"<<endl;
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

CUIComboOrdreChange::~CUIComboOrdreChange() {
}

