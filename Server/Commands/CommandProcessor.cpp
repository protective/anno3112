/* 
 * File:   CommandProcessor.cpp
 * Author: karsten
 * 
 * Created on 9. marts 2014, 12:59
 */

#include "CommandProcessor.h"
#include "Processable.h"
#include "../World/SWorld.h"

CommandProcessor::CommandProcessor(Processable* processable, uint32_t interval, uint32_t firstExecuteTime):
Command(firstExecuteTime){
	_processable = processable;
	_interval = interval;
	_lastExecuteTime = firstExecuteTime;
}

uint32_t CommandProcessor::execute(){
	uint32_t time = world->getTime();
	_processable->proces(time - _lastExecuteTime, _processor);
	_lastExecuteTime = time;
	_time+=_interval;
	_processable->addCommand(this);
	return COMMAND_CONTINUE;
}


CommandProcessor::~CommandProcessor() {
}

