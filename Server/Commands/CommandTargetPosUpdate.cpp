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

	
	if(_processor->getLocalProcssable().find(_message->_Id) == _processor->getLocalProcssable().end()){
		cerr<<"CommandTargetPosUpdate target unit not on processor"<<endl;
		return COMMAND_FINAL;
	}

	/*
	if (it->second->isShip() && it->second->getTeam() == client->getTeamId() && !(it->second->isShip()->getMovementStatus() & MoveBitF::TargetPosLock)){
		SShip* ss = (SShip*)it->second;
		SPos sp;
		if(ss->getPos().grid
			&& (int32_t)0 - ((int32_t)ss->getPos().grid->getWight()/2) < st->_TargetPos_x
			&& (int32_t)0 - ((int32_t)ss->getPos().grid->getHight()/2) < st->_TargetPos_y
			&& st->_TargetPos_x < (int32_t)ss->getPos().grid->getWight()/2
			&& st->_TargetPos_y < (int32_t)ss->getPos().grid->getHight()/2 ){

			sp.x = st->_TargetPos_x;
			sp.y = st->_TargetPos_y;
			sp.d = st->_TargetPos_d;
			ss->setTargetPos(sp);
		}
	}
	*/
	SPos temp(_message->_TargetPos_x,_message->_TargetPos_y,_message->_TargetPos_d);
	if(_processor->getLocalProcssable()[_message->_Id]->isUnit())
		_processor->getLocalProcssable()[_message->_Id]->isUnit()->setTargetPos(temp);
}

CommandTargetPosUpdate::~CommandTargetPosUpdate() {
	free(_message);
}

