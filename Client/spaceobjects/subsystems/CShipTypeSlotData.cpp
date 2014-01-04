/* 
 * File:   CShipTypeSlotData.cpp
 * Author: karsten
 * 
 * Created on 16. august 2011, 23:40
 */

#include "CShipTypeSlotData.h"

CShipTypeSlotData::CShipTypeSlotData(uint32_t slotType, int32_t gX, int32_t gY, uint32_t uiX, uint32_t uiY) {
	_gX = gX;
	_gY = gY;
	_uiX = uiX;
	_uiY = uiY;
	_slotType = slotType;
}



CShipTypeSlotData::~CShipTypeSlotData() {
}

