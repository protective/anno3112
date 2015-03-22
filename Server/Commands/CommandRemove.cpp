/* 
 * File:   CommandRemove.cpp
 * Author: karsten
 * 
 * Created on 9. maj 2014, 23:36
 */

#include "CommandRemove.h"
#include "Processor.h"
#include "CommandExitGrid.h"
#include "CommandUpdateMetas.h"
#include "../World/SGrid.h"
#include "../World/SWorld.h"

CommandRemove::CommandRemove(uint32_t time, Processable* processable) :
Command(world->getTime()){
	_processable = processable;
}

uint32_t CommandRemove::execute(){

	_processor->removeByProcessable(_processable);
	networkControl->deRegisterObj(_processable->getId());
	
	list<MetaRemove> templist;
	MetaRemove temp;
	temp.id = _processable->getId();
	templist.push_back(temp);
	for(map<Processor*, list<uint32_t> >::iterator it = _processor->_lowFrec.begin(); it != _processor->_lowFrec.end(); it++){
		_processor->_lowFrec[it->first].remove(_processable->getId());
		it->first->addCommand(new CommandUpdateMetas(1,templist));
	}
	
	
	//_processor->_lowFrec.erase(_processable->getId());
	//_processor->_medFrec.erase(_processable->getId());
	//_processor->_highFrec.erase(_processable->getId());	
	
	_processable->setProcessor(NULL);
	_processor->getLocalProcssables().erase(_processable->getId());

	delete _processable;
	return COMMAND_FINAL;
}

CommandRemove::~CommandRemove() {
}

