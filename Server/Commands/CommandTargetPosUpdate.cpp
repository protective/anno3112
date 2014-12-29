/* 
 * File:   CommandTargetPosUpdate.cpp
 * Author: karsten
 * 
 * Created on 22. april 2014, 23:25
 */

#include "CommandTargetPosUpdate.h"
#include "Processor.h"
#include "../Sspacebjects/SPos.h"
#include "../Sspacebjects/SUnit.h"
CommandTargetPosUpdate::CommandTargetPosUpdate(uint32_t time, SerialPCShipTargetPosUpdate* message, uint32_t clientId):
Command(time){
	_message = (SerialPCShipTargetPosUpdate*)malloc(sizeof(SerialPCShipTargetPosUpdate));
	memcpy(_message,message,sizeof(SerialPCShipTargetPosUpdate));
	_clientId = clientId;
}

uint32_t CommandTargetPosUpdate::execute(){

	
	if(_processor->getLocalProcssables().find(_message->_Id) == _processor->getLocalProcssables().end()){
		cerr<<"CommandTargetPosUpdate target unit not on processor"<<endl;
		return COMMAND_FINAL;
	}
	SPos temp(_message->_TargetPos_x,_message->_TargetPos_y,_message->_TargetPos_d);
	if(_processor->getLocalProcssables()[_message->_Id]->isUnit())
		_processor->getLocalProcssables()[_message->_Id]->isUnit()->setTargetPos(temp);
}

CommandTargetPosUpdate::~CommandTargetPosUpdate() {
	free(_message);
}

