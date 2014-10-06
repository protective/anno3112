/* 
 * File:   CommandCargoAdd.cpp
 * Author: karsten
 * 
 * Created on 5. oktober 2014, 21:24
 */

#include "CommandCargoAdd.h"
#include "CommandCargoTransOnSender.h"
#include "../Processor.h"
#include "../../Sspacebjects/SUnit.h"
#include "../../Sspacebjects/SSubAble.h"
#include "../../World/SWorld.h"

CommandCargoAdd::CommandCargoAdd(uint32_t toShipId, uint32_t itemType, uint32_t quan):
Command(0){
	_toShipId = toShipId;
	_itemType = itemType;
	_quan = quan;
}


uint32_t CommandCargoAdd::execute(){
	
	cerr<<"execute CommandCargoAdd toshipid = "<<_toShipId<<endl;

	Processable *tproc = _processor->getLocalProcssable(_toShipId);

	uint32_t retMsg = 0;
	cerr<<"hest temtype="<<_itemType<<endl;
	if (!itemlist[_itemType])
		return COMMAND_FINAL;

	cerr<<"hest1 "<<tproc<<endl;
	SCargoBay* targetBay = NULL;
	if(!tproc)
		return COMMAND_FINAL;
	if(!tproc->getsubable())
		return COMMAND_FINAL;

	targetBay = tproc->getsubable()->getCargoBay();
	
	cerr<<"hest2"<<endl;
	if(targetBay){
		cerr<<"hest3"<<endl;
		targetBay->AddReturn(itemlist[_itemType], _quan);	
	}
	return COMMAND_FINAL;
}


CommandCargoAdd::~CommandCargoAdd() {
}

