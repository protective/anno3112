/* 
 * File:   CUIButtonFitLoadout.cpp
 * Author: karsten
 * 
 * Created on 1. marts 2012, 21:45
 */

#include "CUIButtonFitLoadout.h"
#include "../../spaceobjects/subsystems/CLoadout.h"
#include "../../spaceobjects/cargo/CCargoBay.h"
#include "../../spaceobjects/CSubAble.h"
#include "../../spaceobjects/CShip.h"
CUIButtonFitLoadout::CUIButtonFitLoadout(CUIBaseFrame* parrent,CCargoBay* cargo, uint32_t idLoadout):
CUIButton(parrent,0,0,59,14){
	_IdLoadout = idLoadout;
	_cargo = cargo;

}

void CUIButtonFitLoadout::Click(SDL_Event event, int32_t x, int32_t y){
	if(globalLoadout.find(_IdLoadout) != globalLoadout.end() ){
	cerr<<"click Fit loadout>"<<globalLoadout[_IdLoadout]->getName()<<"<"<<endl;
		for(list<CObj*>::iterator it = playerMultiSels.begin(); it != playerMultiSels.end(); it++){
			if ( (*it)->isShip() && (*it)->isShip()->getShipType() == globalLoadout[_IdLoadout]->getShipType())
				playerObj->ServerRequsetFitLoadout((*it)->issubable(),_cargo,globalLoadout[_IdLoadout]);
		}
	}else
		cerr<<"click Fit loadout not found"<<endl;
}

void CUIButtonFitLoadout::Draw(){

	glLoadIdentity();
	font.FaceSize(16);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(_x+_parrent->getX(), _y+_parrent->getY()+13);
	stringstream s;

	if(globalLoadout.find(this->_IdLoadout) != globalLoadout.end())
		s<<globalLoadout[this->_IdLoadout]->getName();
	else
		s<<"Loadout Not Found";
	font.Render(s.str().c_str());
}

CUIButtonFitLoadout::~CUIButtonFitLoadout() {
}

