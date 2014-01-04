/* 
 * File:   SOrdreConditionAND.cpp
 * Author: karsten
 * 
 * Created on 20. februar 2012, 18:34
 */

#include "SOrdreConditionAND.h"
#include "SOrdreCondition.h"

SOrdreConditionAND::SOrdreConditionAND(SOrdreCondition* left, SOrdreCondition* right) {
	_right = right;
	_left = left;
}

bool SOrdreConditionAND::sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
	if(_left && _right && _left->sat(callUnit,triggerUnit,triggerGrid) && _right->sat(callUnit,triggerUnit,triggerGrid))
		return true;
	return false;
}

SOrdreConditionAND::~SOrdreConditionAND() {
}

