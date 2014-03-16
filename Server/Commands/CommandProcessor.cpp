/* 
 * File:   CommandProcessor.cpp
 * Author: karsten
 * 
 * Created on 9. marts 2014, 12:59
 */

#include "CommandProcessor.h"

CommandProcessor::CommandProcessor(Processable* processable, uint32_t interval, uint32_t firstExecuteTime):
Command(firstExecuteTime){
	_processable = processable;
	_interval = interval;
	_lastExecuteTime = firstExecuteTime;
}

void CommandProcessor::execute(){
	uint32_t time = world->getTime();
	_processable->proces(time - _lastExecuteTime);
	_lastExecuteTime = time;
	_processable->addCommand(this);
	return COMMAND_CONTINUE;
	
}


CommandProcessor::~CommandProcessor() {
}

