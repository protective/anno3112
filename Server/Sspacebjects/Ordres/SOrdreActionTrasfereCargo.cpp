/* 
 * File:   SOrdreActionTrasfereCargo.cpp
 * Author: karsten
 * 
 * Created on 21. februar 2012, 20:07
 */

#include "SOrdreActionTrasfereCargo.h"
#include "../../Sspacebjects/SObj.h"
#include "../../Sspacebjects/SSubAble.h"
#include "../../World/SGrid.h"
SOrdreActionTrasfereCargo::SOrdreActionTrasfereCargo(uint32_t transfereTo_oindex) {
	_oindex = transfereTo_oindex;
}

void SOrdreActionTrasfereCargo::execute(SObj* callUnit, SObj* triggerUnit, SGrid* triggerGrid) {
	SObj* transunit = NULL;
	if(callUnit->getOrdreObj().find(_oindex) != callUnit->getOrdreObj().end())
		transunit = callUnit->getOrdreObj()[_oindex];
	
	if(callUnit && callUnit->getsubable() && callUnit->getsubable()->getCargoBay() &&
		transunit && transunit->getsubable() && transunit->getsubable()->getCargoBay()
	){
		for(map<SItemType*, uint32_t>::iterator it = callUnit->getsubable()->getCargoBay()->getContent().begin(); it != callUnit->getsubable()->getCargoBay()->getContent().end(); it++){
			callUnit->getsubable()->getCargoBay()->TransfereCargo(transunit->getsubable()->getCargoBay(),it->first, 100000);
		}
	}

}

SOrdreActionTrasfereCargo::~SOrdreActionTrasfereCargo() {
}

