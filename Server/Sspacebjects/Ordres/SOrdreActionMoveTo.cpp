/* 
 * File:   SOrdreActionMoveTo.cpp
 * Author: karsten
 * 
 * Created on 17. februar 2012, 13:26
 */

#include "SOrdreActionMoveTo.h"
#include "../../Sspacebjects/SObj.h"
#include "../../World/SGrid.h"
SOrdreActionMoveTo::SOrdreActionMoveTo(bool isUnit,uint32_t oindex) {
	_isUnit = isUnit;
	_oindex = oindex;
}



void SOrdreActionMoveTo::execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid) {
	if(_isUnit){
		if(callUnit->getOrdreObj().find(_oindex) != callUnit->getOrdreObj().end())
			callUnit->isMovable()->setTargetPos(callUnit->getOrdreObj()[_oindex]->getPos());
	}else{
		if(callUnit->getOrdrePos().find(_oindex) != callUnit->getOrdrePos().end()){
			callUnit->isMovable()->setTargetPos(*callUnit->getOrdrePos()[_oindex]);
		}
	}
}


SOrdreActionMoveTo::~SOrdreActionMoveTo() {
}

