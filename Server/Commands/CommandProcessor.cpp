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
	if(!firstExecuteTime){
		_lastExecuteTime = world->getTime();
		_time = world->getTime();
	}
}

uint32_t CommandProcessor::execute(){
	
	uint32_t time = world->getTime();
	//cerr<<"processor time"<<time<<endl;
	_processable->proces(_time - _lastExecuteTime, _processor);
	_lastExecuteTime = _time;
	_time += _interval;
	//cerr<<"new time"<<_time<<endl;
	_processable->addCommand(this);
	return COMMAND_CONTINUE;
}


CommandProcessor::~CommandProcessor() {
}

