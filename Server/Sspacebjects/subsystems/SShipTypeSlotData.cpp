/* 
 * File:   SShipTypeSlotData.cpp
 * Author: karsten
 * 
 * Created on 25. juni 2011, 00:21
 */

#include "SShipTypeSlotData.h"

SShipTypeSlotData::SShipTypeSlotData(FitTypes::Enum slotType, int32_t gX, int32_t gY, uint32_t uiX, uint32_t uiY) {
	_gX = gX;
	_gY = gY;
	_uiX = uiX;
	_uiY = uiY;
	_slotType = slotType;
	_mount = 0;
	_firedir = FireDir::ALL;
	_baseItem = NULL;
	_baseItemCount = 0;
}

SShipTypeSlotData::SShipTypeSlotData() {
	_gX = 0;
	_gY = 0;
	_uiX = 0;
	_uiY = 0;
	_slotType = FitTypes::Invalid;
	_mount = 0;
	_firedir = FireDir::ALL;
	_baseItem = NULL;
	_baseItemCount = 0;
}

SShipTypeSlotData::~SShipTypeSlotData() {
}

