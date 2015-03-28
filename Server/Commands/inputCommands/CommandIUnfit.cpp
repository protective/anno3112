/* 
 * File:   CommandIUnfit.cpp
 * Author: karsten
 * 
 * Created on 26. april 2014, 17:01
 */

#include "CommandIUnfit.h"
#include  "../../Sspacebjects/cargo/SCargoBay.h"
#include "../../Sspacebjects/SUnit.h"

#include "../Processor.h"
CommandIUnfit::CommandIUnfit(uint32_t fromId, uint32_t subid,  uint32_t toId, uint32_t quantity, uint32_t clientId):
Command(0){
	_step = 0;
	_fromId = fromId;
	_toId = toId;
	_subid = subid;
	_itemId = 0;
	_quantity = quantity;
	_clientId = clientId;
}
uint32_t CommandIUnfit::execute(){
	cerr<<"execute CommandIUnfit"<<endl;
	if(_quantity > 0 && _toId > 0 && _fromId > 0 && _step == 0){
		
		if(_processor->getLocalProcssables().find(_fromId) == _processor->getLocalProcssables().end()){
			cerr<<"CommandIUnfit _fromId not on processor"<<endl;
			return COMMAND_FINAL;
		}
		SUnit* from = _processor->getLocalProcssables()[_fromId]->isUnit();
		if(!from)
			return COMMAND_FINAL;
		SSubSystem* ss = from->getsubable()->getSubsystem(_subid);
		if(!ss)
			return COMMAND_FINAL;
		_itemId = ss->getItemType()->getTypeID();
		_quantity  = max(_quantity, (uint32_t)ss->Xitem());
		cerr<<"remove "<<_subid<<" "<<_quantity<<endl;
		from->getsubable()->RemoveSub(_subid,_quantity);
		if(_quantity > 0){
			_step = 1;
			networkControl->addCommandToProcesable(this, _toId);
			return COMMAND_CONTINUE;
		}
	}else if(_quantity > 0 && _toId > 0 && _step == 1){
		if(_processor->getLocalProcssables().find(_toId) == _processor->getLocalProcssables().end()){
			cerr<<"CommandIUnfit _toId not on processor"<<endl;
			return COMMAND_FINAL;
		}
		SUnit* from = _processor->getLocalProcssables()[_toId]->isUnit();
		if(!from)
			return COMMAND_FINAL;
		SItemType* item = itemlist[_itemId];
		SCargoBay* bay = from->getsubable()->getCargoBay();
		uint32_t quantityAdded = bay->AddReturn(item, _quantity);
		if(quantityAdded < _quantity){
			//readd the sub that were not room for in cargo
			_quantity = _quantity - quantityAdded;
			_step = 2;
			networkControl->addCommandToProcesable(this,_fromId);
			return COMMAND_CONTINUE;
		}
	}else if(_quantity > 0 && _fromId > 0 && _step == 2){
		if(_processor->getLocalProcssables().find(_fromId) == _processor->getLocalProcssables().end()){
			cerr<<"CommandIUnfit _fromId not on processor"<<endl;
			return COMMAND_FINAL;
		}
		SUnit* from = _processor->getLocalProcssables()[_fromId]->isUnit();
		if(!from)
			return COMMAND_FINAL;
		SSubSystem* ss = from->getsubable()->getSubsystem(_subid);
		if(!ss)
			return COMMAND_FINAL;
		SItemType* item = itemlist[_itemId];
		from->getsubable()->AddSub(item, _subid,_quantity);

	}

	return COMMAND_FINAL;
}


CommandIUnfit::~CommandIUnfit() {
}

