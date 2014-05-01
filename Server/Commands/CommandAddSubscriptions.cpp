/* 
 * File:   CommandAddSubscriptions.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:15
 */

#include "CommandAddSubscriptions.h"
#include "Processor.h"

CommandAddSubscriptions::CommandAddSubscriptions(Processor* subscriber, uint8_t level, list<uint32_t> procesables):
Command(getTime()){
	_subscriber = subscriber;
	_level = level;
	_procesables = procesables;
}

CommandAddSubscriptions::CommandAddSubscriptions(Processor* subscriber, uint8_t level, uint32_t procesable):
Command(getTime()){
	_subscriber = subscriber;
	_level = level;
	_procesables.push_back(procesable);
}

uint32_t CommandAddSubscriptions::execute(){
	cerr<<"execure CommandAddSubscriptions"<<endl;
	switch(_level){
		case 1:{
			_processor->_lowFrec[_processor].splice(_processor->_lowFrec[_processor].end(),_procesables);
			break;
		}
		
	}
	return COMMAND_FINAL;
}

CommandAddSubscriptions::~CommandAddSubscriptions() {
}

