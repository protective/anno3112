/* 
 * File:   CSlotNode.cpp
 * Author: karsten
 * 
 * Created on 31. juli 2011, 23:30
 */

#include "CSlotNode.h"

CSlotNode::CSlotNode(CSubAble* owner, uint32_t id, CShipTypeSlotData* slotdata) {
	this->_subtype = slotdata;
	this->_owner = owner;
	this->_subsys = NULL;
	this->_id = id;
}

CSlotNode::~CSlotNode() {
}

