/* 
 * File:   CommandOrderThread.cpp
 * Author: karsten
 * 
 * Created on 4. september 2014, 22:14
 */

#include "CommandOrderThread.h"
#include "SOrdreProgram.h"

CommandOrderThread::CommandOrderThread(SOrdreProgram* program, OBJID obj):
Command(0){
	_program = program;
	_obj = obj;
	_systemCalls.push_back(systemSetSubsystemFlags);
}


uint32_t CommandOrderThread::execute(){
	while(_mipsCredit){
		_mipsCredit--;		
		switch(_program->program()[_programCounter++]){
		
		
		}
	}
	return COMMAND_REPEAT;
}

//void CommandOrderThread::systemSetSubsystemFlags(void* arg){

//}
CommandOrderThread::~CommandOrderThread() {
}

