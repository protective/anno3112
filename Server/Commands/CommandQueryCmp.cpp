/* 
 * File:   CommandQueryCmp.cpp
 * Author: karsten
 * 
 * Created on 24. september 2014, 19:26
 */

#include "CommandQueryCmp.h"
#include "Processable.h"
#include "../Sspacebjects/SProgrammable.h"
#include "../World/SWorld.h"

CommandQueryCmp::CommandQueryCmp(OBJID programmable) :
Command(0) {
	_procesable = programmable;
	_payload = (uint32_t*)malloc(sizeof(uint32_t)*4);
	_callbackHandler = 1;
	_callbackProgramID = 1;
}


uint32_t CommandQueryCmp::execute() {
	Processable* temp = _processor->getLocalProcssables()[_procesable];
	
	if(!temp )
		return COMMAND_FINAL;
	
	if(temp->isProgrammable())
	{
		temp->isProgrammable()->interrupt(_callbackProgramID,_callbackHandler,_payload, sizeof(uint32_t)*4);
	}
	_time = world->getTime() + myrandom(1500,6000);
	return COMMAND_REPEAT;
}


CommandQueryCmp::~CommandQueryCmp() {
}

