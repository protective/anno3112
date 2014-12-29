/* 
 * File:   CommandIFit.cpp
 * Author: karsten
 * 
 * Created on 26. april 2014, 17:02
 */

#include "CommandIFit.h"
#include  "../../Sspacebjects/cargo/SCargoBay.h"
#include "../../Sspacebjects/SUnit.h"

#include "../Processor.h"

CommandIFit::CommandIFit(uint32_t fromId, uint32_t subid, uint32_t toId, uint32_t quantity, uint32_t itemid, uint32_t clientId):
Command(0){
	_step = 0;
	_fromId = fromId;
	_subid = subid;
	_toId = toId;
	_quantity = quantity;
	_itemId = itemid;
	_clientId = clientId;
}
uint32_t CommandIFit::execute(){
	cerr<<"execute CommandIFit"<<endl;
	if(_processor->getLocalProcssables().find(_toId) == _processor->getLocalProcssables().end()){
		cerr<<"CommandTargetPosUpdate target unit not on processor"<<endl;
		return COMMAND_FINAL;
	}
	

	if(_quantity > 0 && _toId > 0 && _fromId > 0 && _step == 0){
		SUnit* from = _processor->getLocalProcssables()[_fromId]->isUnit();
		if(!from)
			return COMMAND_FINAL;
		SItemType* item = itemlist[_itemId];
		SCargoBay* bay = from->getsubable()->getCargoBay();
		_quantity = bay->RemoveReturn(item, max((uint32_t)4 ,_quantity));
		if(_quantity > 0){
			_step = 1;
			networkControl->addCommandToProcesable(this,_toId);
			return COMMAND_CONTINUE;
		}
	}else if(_quantity > 0 && _toId > 0 && _step == 1){
		SUnit* to = _processor->getLocalProcssables()[_toId]->isUnit();
		if(!to)
			return COMMAND_FINAL;
		
		SItemType* item = itemlist[_itemId];
		
		_quantity -= to->getsubable()->AddSub(item,_subid, _quantity);
		if(_quantity > 0){
			_step = 2;
			networkControl->addCommandToProcesable(this, _fromId);
			return COMMAND_CONTINUE;
		}
	}else if(_quantity > 0 && _toId > 0 && _step == 2){
		SUnit* from = _processor->getLocalProcssables()[_fromId]->isUnit();
		if(!from)
			return COMMAND_FINAL;
		SItemType* item = itemlist[_itemId];
		SCargoBay* bay = from->getsubable()->getCargoBay();
		_quantity = bay->AddReturn(item, _quantity);

	}

	return COMMAND_FINAL;
}

CommandIFit::~CommandIFit() {
}

