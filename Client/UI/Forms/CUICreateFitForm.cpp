/* 
 * File:   CUICreateFitForm.cpp
 * Author: karsten
 * 
 * Created on 15. marts 2012, 19:42
 */

#include "CUICreateFitForm.h"
#include "../CUITextInputField.h"
#include "../Buttons/CUIButtonOK.h"
#include "../Buttons/CUIButtonCancel.h"
#include "../../spaceobjects/CObj.h"
CUICreateFitForm::CUICreateFitForm(CUIBaseFrame* parrent, uint32_t x, uint32_t y):
CUIBaseFrame(parrent){
	_x = x;
	_y = y;
	_wight = 105;
	_hight = 65;
	_UIlevel = 3;
	this->_name = new CUITextInputField(this,5,10,60,14);
	this->add(*this->_name);
	this->_ok = new CUIButtonOK(this,55,30,45,30);
	this->add(*this->_ok);
	this->_cancel = new CUIButtonCancel(this,5,30,45,30);
	this->add(*this->_cancel);
	
	this->_toBeDrawnFront = true;

}


void CUICreateFitForm::Click(SDL_Event event,int32_t x, int32_t y){

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		if (x >=  (*it)->getX() && x <= (*it)->getX() + (*it)->getWight() && y >=  (*it)->getY() && y <= (*it)->getY() + (*it)->getHight() ){
			(*it)->Click(event,x-(*it)->getX(),y-(*it)->getY());
			if((*it) == this->_ok){
				if(playerSels && playerSels->issubable())
					playerObj->ServerRequestCreateLoadout(playerSels->issubable(),this->_name->getTextField());
				this->_canBeRemoved = true;
			}
			if((*it) == this->_cancel){
				this->_canBeRemoved = true;
			}
		}
	}
}
void CUICreateFitForm::Draw(){
	Drawbox(_x+_parrent->getX(),_y+_parrent->getY(),_wight,_hight,0,1,1,1);

	for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
		(*it)->Draw();
	}
}


CUICreateFitForm::~CUICreateFitForm() {
}

