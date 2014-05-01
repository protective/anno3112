/* 
 * File:   CommandAdd.cpp
 * Author: karsten
 * 
 * Created on 25. februar 2014, 22:44
 */

#include "CommandAdd.h"
#include "Processor.h"

CommandAdd::CommandAdd(uint32_t time, Processable* processable,list<Command*> commands) : 
Command(time){
	_commands = commands;
	_processable = processable;
}

uint32_t CommandAdd::execute(){
	cerr<<"execure CommandAdd"<<endl;
	for(list<Command*>::iterator it = _commands.begin(); it != _commands.end();it++){
		_processor->addCommand(*it);
	}
	for(list<Command*>::iterator it = _processable->getLocalQueue().begin(); it != _processable->getLocalQueue().end();it++) {
		_processor->addCommand(*it);
	}
	_processable->setProcessor(_processor);
	_processor->getLocalProcssable()[_processable->getId()] = _processable;
	
	//start reciveing from the network
	networkControl->registerObj(_processable->getId(),_processor);

	return COMMAND_FINAL;
}

CommandAdd::~CommandAdd() {
}

