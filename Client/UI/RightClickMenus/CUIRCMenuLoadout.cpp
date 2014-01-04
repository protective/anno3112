/* 
 * File:   CUIRCMenuLoadout.cpp
 * Author: karsten
 * 
 * Created on 1. marts 2012, 21:39
 */

#include "CUIRCMenuLoadout.h"
#include "../Buttons/CUIButtonFitLoadout.h"
#include "../../spaceobjects/cargo/CCargoBay.h"
#include "../../spaceobjects/CShip.h"
#include "../../spaceobjects/CShipType.h"
#include "../../spaceobjects/subsystems/CLoadout.h"
CUIRCMenuLoadout::CUIRCMenuLoadout(CUIBaseFrame* parrent,uint32_t x,uint32_t y,uint32_t hight, CCargoBay* cargo):
CUIRightClickMenu(parrent,x,y,60,hight){
	cerr<<"loadout size"<<globalLoadout.size()<<endl;
	this->_spreadX = 60;
	this->_spreadY = 14;
	for(map<uint32_t,CLoadout*>::iterator it = globalLoadout.begin(); it != globalLoadout.end(); it++){

		if(playerSels && playerSels->isShip() && it->second->getShipType() == playerSels->isShip()->getShipType())
			this->AddButton(*new CUIButtonFitLoadout(this,cargo,it->first));
	}
	this->ToBeDrawFront();
}


CUIRCMenuLoadout::~CUIRCMenuLoadout() {
}

