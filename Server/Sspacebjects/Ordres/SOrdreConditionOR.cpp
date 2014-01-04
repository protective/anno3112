/* 
 * File:   SOrdreConditionOR.cpp
 * Author: karsten
 * 
 * Created on 20. februar 2012, 18:35
 */

#include "SOrdreConditionOR.h"

SOrdreConditionOR::SOrdreConditionOR(SOrdreCondition* left, SOrdreCondition* right) {
	_right = right;
	_left = left;
}


bool SOrdreConditionOR::sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
	if(_left && _right && ( _left->sat(callUnit,triggerUnit,triggerGrid) || _right->sat(callUnit,triggerUnit,triggerGrid)))
		return true;
	return false;
}

SOrdreConditionOR::~SOrdreConditionOR() {
}

