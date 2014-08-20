/* 
 * File:   SMetaObj.cpp
 * Author: karsten
 * 
 * Created on 22. februar 2014, 11:48
 */

#include <limits.h>

#include "SMetaObj.h"
#include "../World/SWorld.h"
SMetaObj::SMetaObj(uint32_t id) {
	_id = id;
	_size = 0;
	owner = 0;
	team = 0;
	procesNodeId = 0;
//	posValid = false;
}
SPos SMetaObj::getRPos(){
	int32_t delta = world->getTime() - _timerLowFeq;
	SPos temp;

	temp.x = pos.x + ((vecX * delta)/40);
	temp.y = pos.y + ((vecY * delta)/40);
	temp.z = pos.z + ((vecZ * delta)/40);
	
	return temp;
}


bool SMetaObj::isMoveable(){
	switch(targetType){
		case TargetType::Capital:
		case TargetType::Fighter:
		case TargetType::Freighter:
		case TargetType::Frigat:
		case TargetType::HeavySupport:
		case TargetType::LightSupport:
		case TargetType::MiningShip:
		case TargetType::Missel:
		case TargetType::SuperCapital:
		case TargetType::Unarmed:
			return true;
		default:
			return false;
	}
			
	return false;
}


SMetaObj::~SMetaObj() {
}

