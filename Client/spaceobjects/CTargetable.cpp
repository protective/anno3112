/* 
 * File:   GTargetable.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:32
 */

#include "CTargetable.h"

CTargetable::CTargetable(CObj* obj) {
	this->_obj = obj;
	this->_prio = 0;
}

CTargetable::~CTargetable() {
}

