/* 
 * File:   CommandUpdateMetas.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:38
 */

#include "CommandUpdateMetas.h"
#include "Command.h"

CommandUpdateMetas::CommandUpdateMetas(uint8_t freq, list<MetaLow> objToSend):
Command(world->getTime){
	_freq;
	_objToSend = objToSend;
}

uint32_t CommandUpdateMetas::execute(){
	for(list<MetaLow>::iterator it = _objToSend.begin(); it != _objToSend.end();it++){
		_processor->_metaObjs[*it->id].pos = *it->pos;
		_processor->_metaObjs[*it->id].scan = *it->scan;
		_processor->_metaObjs[*it->id].scanP = *it->scanP;
		_processor->_metaObjs[*it->id].procesNodeId = *it->procesNodeId;
	}

	return COMMAND_FINAL;
}

CommandUpdateMetas::~CommandUpdateMetas() {
}

