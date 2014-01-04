/* 
 * File:   SOrdreConditionUnitEqTo.cpp
 * Author: karsten
 * 
 * Created on 20. februar 2012, 18:28
 */

#include "SOrdreConditionUnitEqTo.h"
#include "../SObj.h"
SOrdreConditionUnitEqTo::SOrdreConditionUnitEqTo(OrdresConditionUnits::Enum conditionUnit, uint32_t oindexUnit) {
 _conditionUnit = conditionUnit;
 _oindexUnit = oindexUnit;
}

bool SOrdreConditionUnitEqTo::sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
	if (!callUnit)
		return false;
	if(_conditionUnit == OrdresConditionUnits::TriggerUnit)
		return triggerUnit == triggerUnit;
	else if(_conditionUnit == OrdresConditionUnits::OindexUnit){
		if(callUnit->getOrdreObj().find(_oindexUnit) != callUnit->getOrdreObj().end())
			return triggerUnit == callUnit->getOrdreObj()[_oindexUnit];
	}
	return false;
}

SOrdreConditionUnitEqTo::~SOrdreConditionUnitEqTo() {
}

