/* 
 * File:   CommandQueryRsp.cpp
 * Author: karsten
 * 
 * Created on 26. september 2014, 17:57
 */

#include "CommandQueryRsp.h"
#include "../../Sspacebjects/SProgrammable.h"
#include "../../World/SWorld.h"
#include "../Processor.h"
CommandQueryRsp::CommandQueryRsp(OBJID reciver, list<qureyRow> rspData):
Command(0){
	_reciver = reciver;
	_rspData = rspData;
}

uint32_t CommandQueryRsp::execute(){


	//for(list<qureyRow>::iterator it = _rspData.begin(); it != _rspData.end();it++){
		//cerr<<"obj="<<(*it).objId<<" attri="<<(*it).attri<<" value="<<(*it).value<<endl;
	//}
	//cerr<<endl;
	
	if(_processor->getLocalProcssables().find(_reciver) == _processor->getLocalProcssables().end())
		return COMMAND_FINAL;
	
	Processable* temp = _processor->getLocalProcssables()[_reciver];
	
	if(!temp )
		return COMMAND_FINAL;
	
	if(temp->isProgrammable())
	{
		uint32_t rsp[3];
		
		rsp[0] = _rspData.back().objId;
		rsp[1] = uint32_t(_rspData.back().attri & 0x7FFFFFFF);
		rsp[2] = _rspData.back().value;

		
		temp->isProgrammable()->interrupt(1,2,rsp, 12);
	}
	_time = world->getTime() + myrandom(1500,6000);
	return COMMAND_FINAL;
}

CommandQueryRsp::~CommandQueryRsp() {
}

