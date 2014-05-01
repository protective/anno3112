/* 
 * File:   CommandTransfere.cpp
 * Author: karsten
 * 
 * Created on 25. februar 2014, 23:17
 */

#include "CommandTransfere.h"
#include "CommandAdd.h"
#include "Processor.h"
CommandTransfere::CommandTransfere(uint32_t time, Processor* toProcessor, Processable* toTransfere) :
Command(time){
	_toTransfere = toTransfere;
	_toProcessor = toProcessor;
}

uint32_t CommandTransfere::execute(){
	cerr<<"execure CommandTransfere"<<endl;
	CommandAdd* temp = new CommandAdd(0,_toTransfere,_toTransfere->getProcessor()->removeByProcessable(_toTransfere));
	_toProcessor->addCommand(temp);
	return COMMAND_FINAL;
}

CommandTransfere::~CommandTransfere() {
}

