/* 
 * File:   CommandOrderThread.cpp
 * Author: karsten
 * 
 * Created on 4. september 2014, 22:14
 */

#include "CommandOrderThread.h"
#include "SOrdreProgram.h"
#include "Compiler/CommandCompiler.h"
#include "../../World/SWorld.h"
#include "../SProgrammable.h"
#include "../../Commands/Processor.h"


CommandOrderThread::CommandOrderThread(OBJID obj):
Command(0){
	_procesable = obj;
}


uint32_t CommandOrderThread::execute(){
	Processable* temp = _processor->getLocalProcssables()[_procesable];
	
	if(!temp )
		return COMMAND_FINAL;
	
	if(temp->isProgrammable())
	{
		return temp->isProgrammable()->execute(this);
	}
	return COMMAND_FINAL;
}

CommandOrderThread::~CommandOrderThread() {
}

