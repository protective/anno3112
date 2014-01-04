/* 
 * File:   CSubSystem.cpp
 * Author: karsten
 * 
 * Created on 31. juli 2011, 23:37
 */

#include "CSubSystem.h"

CSubSystem::CSubSystem(CObj& owner,CSlotNode& slotnode,uint32_t id) {
	this->_owner = &owner;
	this->_slotnode = &slotnode;
	this->_id = id;
	_online = false;
	_recharge = false;
	_graficCounter = 0;
}



CSubSystem::~CSubSystem() {
}

