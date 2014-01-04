/* 
 * File:   SOrdreConditionStatOp.cpp
 * Author: karsten
 * 
 * Created on 20. februar 2012, 18:29
 */

#include "SOrdreConditionStatOp.h"
#include "../SObj.h"
#include "../SSubAble.h"
SOrdreConditionStatOp::SOrdreConditionStatOp(OrdreConditionsStat::Enum conditionstat, int32_t value) {
	_conditionstat = conditionstat;
	_value = value;
}

bool SOrdreConditionStatOp::sat(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid){
	switch(_conditionstat){
		case OrdreConditionsStat::CargoGreaterThen:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() ){
				if (callUnit->getsubable()->getCargoBay()->getcurCargo() > _value)
					return true;
			}
			break;
		}
		case OrdreConditionsStat::CargoLessThen:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() ){
				if (callUnit->getsubable()->getCargoBay()->getcurCargo() < _value)
					return true;
			}
			break;
		}
		case OrdreConditionsStat::CargoEqualTo:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() ){
				if (callUnit->getsubable()->getCargoBay()->getcurCargo() == _value)
					return true;
			}
			break;
		}
		case OrdreConditionsStat::CargoPGreaterThen:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() && callUnit->getsubable()->getCargoBay()->getmaxCargo()){
				if ((callUnit->getsubable()->getCargoBay()->getcurCargo()*100) / callUnit->getsubable()->getCargoBay()->getmaxCargo() > _value)
					return true;
			}
			break;
		}
		case OrdreConditionsStat::CargoPLessThen:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() && callUnit->getsubable()->getCargoBay()->getmaxCargo()){
				if ((callUnit->getsubable()->getCargoBay()->getcurCargo()*100) / callUnit->getsubable()->getCargoBay()->getmaxCargo() < _value)
					return true;
			}
			break;
		}
		case OrdreConditionsStat::CargoPEqualTo:{
			if(callUnit->getsubable() && callUnit->getsubable()->getCargoBay() && callUnit->getsubable()->getCargoBay()->getmaxCargo()){
				if ((callUnit->getsubable()->getCargoBay()->getcurCargo()*100) / callUnit->getsubable()->getCargoBay()->getmaxCargo() == _value)
					return true;
			}
			break;
		}
		default:{

		}
	}
	return false;
}


SOrdreConditionStatOp::~SOrdreConditionStatOp() {
}

