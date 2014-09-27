/* 
 * File:   CommandCargoTransfere.cpp
 * Author: karsten
 * 
 * Created on 25. september 2014, 23:01
 */

#include "CommandCargoTransfere.h"
#include "CommandCargoTransMsg.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/SSubAble.h"
#include "../../World/SWorld.h"

CommandCargoTransfere::	CommandCargoTransfere(uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan) :
Command(0){
	_fromShipId = fromShipId;
	_toShipId = toShipId;
	_itemType = itemType;
	_remaingQuan = quan;
}


uint32_t CommandCargoTransfere::execute(){
	
	cerr<<"execute CommandCargoTransfere"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_fromShipId);
	if (!tproc)
		return COMMAND_FINAL;
	SUnit* unit = tproc->isUnit();
	if (!unit)
		return COMMAND_FINAL;
	if (!itemlist[_itemType])
		return COMMAND_FINAL;
	
	uint32_t qToTransfere = unit->getsubable()->getCargoBay()->RemoveReturn(itemlist[_itemType],min((uint32_t)2,_remaingQuan));
	if (qToTransfere){
		CommandCargoTransMsg* t= new CommandCargoTransMsg(_fromShipId, _toShipId, _itemType, qToTransfere);
		if (networkControl->addCommandToProcesable(t,_toShipId))
			delete t;
		else
			_remaingQuan -= qToTransfere;
	}else{
		return COMMAND_FINAL;
	}
		_time = world->getTime() + 500;
	return _remaingQuan ? COMMAND_REPEAT : COMMAND_FINAL;
}

CommandCargoTransfere::~CommandCargoTransfere() {
}

