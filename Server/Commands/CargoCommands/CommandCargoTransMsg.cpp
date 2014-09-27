/* 
 * File:   CommandCargoTransMsg.cpp
 * Author: karsten
 * 
 * Created on 25. september 2014, 23:02
 */

#include "CommandCargoTransMsg.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/SSubAble.h"
CommandCargoTransMsg::CommandCargoTransMsg(uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan):
Command(0) {
	
	_fromShipId = fromShipId;
	_toShipId = toShipId;
	_itemType = itemType;
	_quan = quan;
}


uint32_t CommandCargoTransMsg::execute(){
	
	cerr<<"execute CommandCargoTransMsg"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_toShipId);
	if (!tproc)
		return COMMAND_FINAL;
	SUnit* unit = tproc->isUnit();
	if (!unit)
		return COMMAND_FINAL;

	if(!itemlist[_itemType])
		return COMMAND_FINAL;
	unit->getsubable()->getCargoBay()->AddReturn(itemlist[_itemType],_quan);
	
	return COMMAND_FINAL;
}

CommandCargoTransMsg::~CommandCargoTransMsg() {
}

