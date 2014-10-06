/* 
 * File:   CommandCargoTransfere.cpp
 * Author: karsten
 * 
 * Created on 25. september 2014, 23:01
 */

#include "CommandCargoTransOnReciver.h"
#include "CommandCargoTransOnSender.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/SSubAble.h"
#include "../../World/SWorld.h"

CommandCargoTransOnReciver::CommandCargoTransOnReciver(uint32_t id, uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan) :
Command(0){
	_id = id;
	_fromShipId = fromShipId;
	_toShipId = toShipId;
	_itemType = itemType;
	_quan = quan;
}


uint32_t CommandCargoTransOnReciver::execute(){
	
	cerr<<"execute CommandCargoTransfOnReciver"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_toShipId);

	uint32_t retAdded = 0;
	uint32_t toAdd = _quan;
	uint32_t retMsg = 0;
	
	if (!itemlist[_itemType])
		retMsg = 1;

	SCargoBay* targetBay = NULL;
	if(!tproc || !tproc->getsubable() || !tproc->getsubable()->getCargoBay()){
		retMsg = 1;
	}else{
		targetBay = tproc->getsubable()->getCargoBay();
	}
	
	if(targetBay && retMsg == 0){

		//test how much we can recive
		toAdd = targetBay->useIncommingCredit(_quan);
		//recive it
		retAdded = targetBay->AddReturn(itemlist[_itemType], toAdd);
		
		if(retAdded < toAdd){
			retMsg = 1;
		}		
	}
	CommandCargoTransOnSender* s
			= new CommandCargoTransOnSender(_id,
			_fromShipId,
			_toShipId,
			retMsg,
			_quan - retAdded);
	if (networkControl->addCommandToProcesable(s,_fromShipId))
		delete s;
		
	return COMMAND_FINAL;
}

CommandCargoTransOnReciver::~CommandCargoTransOnReciver() {
}

