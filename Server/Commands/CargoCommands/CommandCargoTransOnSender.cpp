/* 
 * File:   CommandCargoTransMsg.cpp
 * Author: karsten
 * 
 * Created on 25. september 2014, 23:02
 */

#include "CommandCargoTransOnSender.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/SSubAble.h"
CommandCargoTransOnSender::CommandCargoTransOnSender(uint32_t id, uint32_t fromShipId, uint32_t toShipId, uint32_t retmsg, uint32_t quan):
Command(0) {
	_id = id;
	_fromShipId = fromShipId;
	_toShipId = toShipId;
	_retmsg = retmsg;
	_quan = quan;
}


uint32_t CommandCargoTransOnSender::execute(){
	
	cerr<<"execute CommandCargoTransOnSender"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_fromShipId);
	if (!tproc)
		return COMMAND_FINAL;
	SUnit* unit = tproc->isUnit();
	if (!unit || !unit->getsubable() || !unit->getsubable()->getCargoBay())
		return COMMAND_FINAL;

	SCargoBay* bay = unit->getsubable()->getCargoBay();

	if(bay->getTransferes().find(_id) == bay->getTransferes().end()){
		return COMMAND_FINAL;
	}
	
	//we failed to add everything
	if(_quan){
		SItemType* item = itemlist[bay->getTransferes()[_id]._itemId];
		bay->AddReturn(item,_quan);
		bay->getTransferes()[_id]._remaning += _quan;
	}
	
	
	//somthing terminated the transfere.
	if(_retmsg){
		bay->getTransferes().erase(_id);
	}
	return COMMAND_FINAL;
}

CommandCargoTransOnSender::~CommandCargoTransOnSender() {
}

