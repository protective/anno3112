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
}


uint32_t CommandOrderThread::execute(){
	while(_mipsCredit){
		_mipsCredit--;		
		switch(_program->program()[_programCounter++]){
		
		
		}
	}
	return COMMAND_REPEAT;
}


CommandOrderThread::~CommandOrderThread() {
}

