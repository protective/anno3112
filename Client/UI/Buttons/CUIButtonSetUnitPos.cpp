/* 
 * File:   CUIButtonSetUnitPos.cpp
 * Author: karsten
 * 
 * Created on 27. februar 2012, 08:35
 */

#include "CUIButtonSetUnitPos.h"
#include "../CUIMainFrame.h"
CUIButtonSetUnitPos::CUIButtonSetUnitPos(CUIBaseFrame* parrent, int32_t setUnit, int32_t setPos):
CUIButton(parrent,0,550,100,12){
	_setUnit = setUnit;
	_setPos = setPos;
}


void CUIButtonSetUnitPos::Click(SDL_Event event,int32_t x, int32_t y){
	
	if(this->_setUnit >= 0)
		mainFrame->setsetOrdreUnit(this->_setUnit);
	if(this->_setPos >= 0 )
		mainFrame->setsetOrdrePos(this->_setPos);
}

void CUIButtonSetUnitPos::Draw(){

	glLoadIdentity();
	font.FaceSize(16);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
	stringstream s;
	if(this->_setUnit >= 0){
		switch(this->_setUnit){
			case 0: {s<<"Mining Unit"; break;}
			case 1: {s<<"Drop of Unit"; break;}
		}
	}
	if(this->_setPos >= 0){
		switch(this->_setPos){
			case 0: {s<<"Mining Pos"; break;}
		}
	}
	
	font.Render(s.str().c_str());

}

CUIButtonSetUnitPos::~CUIButtonSetUnitPos() {
}

