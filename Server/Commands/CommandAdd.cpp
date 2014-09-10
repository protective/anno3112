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
	//cerr<<"create cmd add id="<<_processable->getId()<<endl;
}

uint32_t CommandAdd::execute(){
	//cerr<<"execure CommandAdd to processor="<<_processable<<" id="<<_processable->getId()<<endl;
	for(list<Command*>::iterator it = _commands.begin(); it != _commands.end();it++){
		_processor->addCommand(*it);
	}
	for(list<Command*>::iterator it = _processable->getLocalQueue().begin(); it != _processable->getLocalQueue().end();it++) {
		_processor->addCommand(*it);
	}
	_processable->setProcessor(_processor);
	_processor->getLocalProcssables()[_processable->getId()] = _processable;
	
	//start reciveing from the network
	networkControl->registerObj(_processable->getId(),_processor);

	return COMMAND_FINAL;
}

CommandAdd::~CommandAdd() {
}

