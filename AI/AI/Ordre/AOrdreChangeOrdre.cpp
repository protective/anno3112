/* 
 * File:   AOrdreChangeOrdre.cpp
 * Author: karsten
 * 
 * Created on 25. juli 2012, 15:37
 */

#include "AOrdreChangeOrdre.h"
#include "spaceobjects/CShip.h"

AOrdreChangeOrdre::AOrdreChangeOrdre(AObjGroup* units, uint32_t ordreIndex) {
	_units = units;
	_ordreIndex = ordreIndex;
}

void AOrdreChangeOrdre::Execute(){
	for (map<uint32_t, CObj*>::iterator it = _units->getobjs().begin(); it != _units->getobjs().end(); it ++){
		uint32_t tempindex = 0;
		if(_ordreIndex == 3){
			if(it->second && it->second->isShip()){
				if( it->second->isShip()->getShipType()->getId() == 1)
					tempindex = 3;
				else if (it->second->isShip()->getShipType()->getId() == 6)
					tempindex = 4;
				else if (it->second->isShip()->getShipType()->getId() == 16)
					tempindex = 1;
				else if (it->second->isShip()->getShipType()->getId() == 46)
					tempindex = 1;			
			}else
				tempindex = _ordreIndex;
		}else
			tempindex = _ordreIndex;
		if(it->second->isShip() && (!it->second->isShip()->getOrdres() ||(it->second->isShip()->getOrdres() && it->second->isShip()->getOrdres()->getId() != tempindex))){
			playerObj->ServerRequestChangeOrdre(it->second,globalOrders[tempindex]);
		}	
	}
}

AOrdreChangeOrdre::~AOrdreChangeOrdre() {
}

