/* 
 * File:   AFunctions.cpp
 * Author: karsten
 * 
 * Created on 5. juni 2012, 23:07
 */

#include "AFunctions.h"
#include "spaceobjects/CObj.h"
#include "spaceobjects/CShip.h"

uint32_t getShipCount(uint32_t playerId, CShipType* shipType, CObj* center, uint32_t range){
	uint32_t counter = 0;
	if(center){
		for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin(); it != playerObj->getObjs().end(); it++){
			if(it->second->getPlayerId() == playerId && it->second->isShip() && it->second->isShip()->getShipType() == shipType && Rangeobj(center->getPos(),it->second->getPos()) <= range){
				counter++;
			}
		}
	}else
		return 0;
	return counter;
}

uint32_t getShipCount(uint32_t playerId, CShipType* shipType){
	uint32_t counter = 0;
	for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin(); it != playerObj->getObjs().end(); it++){
		if(it->second->getPlayerId() == playerId && it->second->isShip() && it->second->isShip()->getShipType() == shipType){
			counter++;
		}
	}
	return counter;
}

