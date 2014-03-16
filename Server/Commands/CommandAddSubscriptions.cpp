/* 
 * File:   CommandAddSubscriptions.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:15
 */

#include "CommandAddSubscriptions.h"

CommandAddSubscriptions::CommandAddSubscriptions(Processor* subscriber, uint8_t level, list<uint32_t> procesables):
Command(getTime()){
	_subscriber = subscriber;
	_level = level;
	_procesables = procesables;
}
uint32_t CommandAddSubscriptions::execute(){
	switch(_level){
		case 1:{
			_processor->_lowFrec[_subscriber->getId()].splice(_processor->_lowFrec[_subscriber->getId()].end(),_procesables);
			break;
		}
		
	}
	return COMMAND_FINAL;
}

CommandAddSubscriptions::~CommandAddSubscriptions() {
}

