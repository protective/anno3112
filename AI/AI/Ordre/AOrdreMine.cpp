/* 
 * File:   AOrdreMine.cpp
 * Author: karsten
 * 
 * Created on 2. juli 2012, 21:05
 */

#include "AOrdreMine.h"
#include "spaceobjects/subsystems/CSubSystemW.h"

AOrdreMine::AOrdreMine(CObj* unit, CSubAble* dropof, CPos* location) {
	_unit = unit;
	_dropof = dropof;
	_location = location;
}

void AOrdreMine::Execute(){
	
	if( _dropof){
		if (_unit->isMovable()){
			_unit->isMovable()->getTargetPos().x = _location->x;
			_unit->isMovable()->getTargetPos().y = _location->y;
		}
		playerObj->ServerNotisTargetPosChange(*_unit);
		playerObj->ServerRequestSetOrdreUnit(_unit,_dropof->obj(),0);
		playerObj->ServerRequestSetOrdrePos(_unit,_location,0);
	}
}


AOrdreMine::~AOrdreMine() {
}

