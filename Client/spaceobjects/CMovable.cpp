/* 
 * File:   GMovable.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:33
 */

#include "CMovable.h"

CMovable::CMovable(CObj* obj, int32_t topSpeed, uint32_t agility) {
	_obj = obj;
	_topSpeed = topSpeed * 100;
	_agility = agility;
	_speed = 0;
	_ofsetX = 0;
	_ofsetY = 0;
	_MovementStatus = 0;
}


CMovable::~CMovable() {
}

CPos& CMovable::getTargetPos(){
	return this->_targetPos;
}