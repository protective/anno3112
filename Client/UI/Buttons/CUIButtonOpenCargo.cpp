/* 
 * File:   CUIButtonOpenCargo.cpp
 * Author: karsten
 * 
 * Created on 1. oktober 2011, 21:08
 */

#include "CUIButtonOpenCargo.h"
#include "../../spaceobjects/CShip.h"
#include "../CUICargoViewer.h"
#include "../CUIMainFrame.h"
CUIButtonOpenCargo::CUIButtonOpenCargo(CUIBaseFrame* parrent, uint32_t x, uint32_t y,uint32_t wight, uint32_t hight):
CUIButton(parrent,x,y,wight,hight){
	_icon = Icontex::Cargo;
}


void CUIButtonOpenCargo::Click(SDL_Event event,int32_t x, int32_t y){
		cerr<<"click open cargo button"<<endl;
	if (playerSels){
		if(playerSels->isShip()){
			CShip* ss = playerSels->isShip();
			for (list<CCargoBay*>::iterator it = mainFrame->getOpenCargoList().begin(); it != mainFrame->getOpenCargoList().end();it++){
				if ((*it) == ss->getCargoBay()){
					return;
				}
			}
			CUICargoViewer* temp = new CUICargoViewer(mainFrame,200,10,160,110,ss->getCargoBay());
			mainFrame->add(*temp);
			mainFrame->getOpenCargoList().push_back((ss->getCargoBay()));
		}
	}
}



CUIButtonOpenCargo::~CUIButtonOpenCargo() {
}

