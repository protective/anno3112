/* 
 * File:   CommandAdd.cpp
 * Author: karsten
 * 
 * Created on 25. februar 2014, 22:44
 */

#include "CommandAdd.h"

CommandAdd::CommandAdd(uint32_t time, Processable* obj,list<Command*> commands) : 
Command(time){
	_commands = commands;
	_obj = obj;
}

uint32_t CommandAdd::execute(){
	for(list<Command*>::iterator it = _commands.begin(); it != _commands.end();it++) 
		_processor->addCommand(*it);
	_processor->getLocalProcssable()[_obj->getId()] = _obj;
	if(_obj->isMetable())
		_obj->getMetaObj(&_processor->getLocalMetas()[_obj->getId()]);
	return COMMAND_FINAL;
}

CommandAdd::~CommandAdd() {
}

