/* 
 * File:   CUIButtonChangeOrdre.cpp
 * Author: karsten
 * 
 * Created on 14. januar 2012, 01:43
 */

#include "CUIButtonChangeOrdre.h"

CUIButtonChangeOrdre::CUIButtonChangeOrdre(CUIBaseFrame* parrent, COrdres* changeTo):
CUIButton(parrent,0,0,40,14){
	this->_changeTo = changeTo;
}

void CUIButtonChangeOrdre::Click(SDL_Event event,int32_t x, int32_t y){
		if (playerSels){
			for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
					playerObj->ServerRequestChangeOrdre(*it,this->_changeTo);
			}

		}
}

void CUIButtonChangeOrdre::Draw(){

	glLoadIdentity();
	font.FaceSize(16);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
	stringstream s;
	s<<_changeTo->getName();
	font.Render(s.str().c_str());

}


CUIButtonChangeOrdre::~CUIButtonChangeOrdre() {
}

