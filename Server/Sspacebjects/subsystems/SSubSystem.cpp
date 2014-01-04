/* 
 * File:   SSubSystem.cpp
 * Author: karsten
 * 
 * Created on 25. juni 2011, 00:19
 */

#include "SSubSystem.h"

SSubSystem::SSubSystem(SObj& owner,SSlotNode& slotnode,uint32_t id) {
	this->_owner = &owner;
	this->_slotnode = &slotnode;
	this->_id = id;
	this->_targetGroup = TargetGroup::Primary;
	this->_cooldown = 0;
	this->_maxcooldown = 0;
}




SSubSystem::~SSubSystem() {
}

