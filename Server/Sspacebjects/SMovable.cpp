/* 
 * File:   SMovable.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:33
 */

#include "SMovable.h"

SMovable::SMovable(SObj* obj, int32_t topSpeed, uint32_t agility) {
	this->_obj =obj;
	_topSpeed = topSpeed* 100;
	_speed = 0;
	_agility = agility;
	_MovementStatus = 0;
}


SMovable::~SMovable() {
}

SPos& SMovable::getTargetPos(){
	return this->_targetPos;
}

void SMovable::setTargetPos(SPos& pos){
	this->_targetPos.x = pos.x;
	this->_targetPos.y = pos.y;
	this->_targetPos.d = pos.d;
	this->obj()->setUpdateCounter(0);
}

