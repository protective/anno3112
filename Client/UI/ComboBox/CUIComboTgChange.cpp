/* 
 * File:   CUIComboTgChange.cpp
 * Author: karsten
 * 
 * Created on 17. oktober 2011, 08:22
 */

#include "CUIComboTgChange.h"
#include "../CUIMainFrame.h"
#include "../../spaceobjects/subsystems/CSlotNode.h"
CUIComboTgChange::CUIComboTgChange(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t wight,uint32_t hight):
CUIComboBox(parrent,x,y,wight,hight)
{
	
}

void CUIComboTgChange::Draw(){

	if (_active){
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY*(1+_frames.size()),0.4,0.1,0.1,1);
		for (list<CUIBaseFrame*>::iterator it = _frames.begin(); it != _frames.end(); it++){
			(*it)->Draw();
		}
	}else{
		Drawbox(this->getX(),this->getY(),this->getWight(),_spreadY,0.4,0.1,0.1,1);
	}

	if (mainFrame->GetSelSlot()){
		if (mainFrame->GetSelSlot()->getSS()){
			glLoadIdentity();
			font.FaceSize(16);
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
			stringstream s;
			s<<getTargetGroupstring(mainFrame->GetSelSlot()->getSS()->getTargetGroup());
			font.Render(s.str().c_str());
			}
	}
}

CUIComboTgChange::~CUIComboTgChange() {
}

