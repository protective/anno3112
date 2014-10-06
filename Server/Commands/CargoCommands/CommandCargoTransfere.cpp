/* 
 * File:   CommandCargoTransfere.cpp
 * Author: karsten
 * 
 * Created on 1. oktober 2014, 23:05
 */

#include "CommandCargoTransfere.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/cargo/SCargoBay.h"
CommandCargoTransfere::CommandCargoTransfere(uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan):
Command(0){
	_fromShipId = fromShipId;
	_toShipId = toShipId;
	_itemType = itemType;
	_quan = quan;
}


uint32_t CommandCargoTransfere::execute(){
	
	cerr<<"execute CommandCargoTransfere"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_fromShipId);
	if (!tproc)
		return COMMAND_FINAL;
	SUnit* unit = tproc->isUnit();
	if (!unit || !unit->getsubable() || !unit->getsubable()->getCargoBay())
		return COMMAND_FINAL;

	if (!itemlist[_itemType])
		return COMMAND_FINAL;
		
	unit->getsubable()->getCargoBay()->addTransfere(_toShipId,_itemType,_quan);

	return COMMAND_FINAL;
}
CommandCargoTransfere::~CommandCargoTransfere() {
}

