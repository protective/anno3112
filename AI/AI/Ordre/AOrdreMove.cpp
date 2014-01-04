/* 
 * File:   AOrdreMove.cpp
 * Author: karsten
 * 
 * Created on 20. juni 2012, 18:42
 */

#include "AOrdreMove.h"


AOrdreMove::AOrdreMove(AObjGroup* units, CPos moveto){
	_units = units;
	_moveto = moveto;
}

void AOrdreMove::Execute(){
	for (map<uint32_t, CObj*>::iterator it = _units->getobjs().begin(); it != _units->getobjs().end(); it ++){
		if (it->second->isMovable()){
			it->second->isMovable()->getTargetPos().x = _moveto.x + myrandom(0,20000)-10000;
			it->second->isMovable()->getTargetPos().y = _moveto.y + myrandom(0,20000)-10000;
		}
		playerObj->ServerNotisTargetPosChange(*it->second);
	}
}

AOrdreMove::~AOrdreMove() {
}

