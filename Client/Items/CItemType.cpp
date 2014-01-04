/* 
 * File:   CItemType.cpp
 * Author: karsten
 * 
 * Created on 1. august 2011, 00:51
 */

#include "CItemType.h"
#include "../spaceobjects/subsystems/CSubType.h"

CItemType::CItemType(uint32_t typeID,uint32_t picID) {
	this->_typeID = typeID;
	this->_picID = picID;
	this->_shiptype = NULL;
	this->_subtype = NULL;
	this->_mass = 0;
	this->_batchSize = 1;
}

CSubType* CItemType::getSubType(){
	return this->_subtype;
}

void CItemType::setSubType(CSubType* subtype){
	this->_subtype = subtype;
}

CItemType::~CItemType() {
}

