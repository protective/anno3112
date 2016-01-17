/* 
 * File:   CommandAddSubscriptions.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:15
 */

#include "CommandAddSubscriptions.h"
#include "Processor.h"
#include "../World/SWorld.h"
/*
CommandAddSubscriptions::CommandAddSubscriptions(Processor* subscriber, SubscriptionLevel::Enum level, list<uint32_t> procesables):
Command(world->getTime()){
	_subscriber = subscriber;
	_level = level;
	_procesables = procesables;
}

CommandAddSubscriptions::CommandAddSubscriptions(Processor* subscriber, SubscriptionLevel::Enum level, uint32_t procesable):
Command(0){
	_subscriber = subscriber;
	_level = level;
	//cerr<<"create command add subscription level="<<level<<endl;
	_procesables.push_back(procesable);
}

uint32_t CommandAddSubscriptions::execute(){
	//cerr<<"execure CommandAddSubscriptions level ="<<_level<<endl;

	switch(_level){
		case SubscriptionLevel::lowFreq:{
			for(list<uint32_t>::iterator it = _procesables.begin(); it != _procesables.end() ; it++){
				//cerr<<"add low freq id ="<<*it<<endl;
			}
			_processor->_lowFrec[_subscriber].splice(_processor->_lowFrec[_subscriber].end(),_procesables);
			break;
		}
		case SubscriptionLevel::Init:{
			_processor->_initsFrec[_subscriber].splice(_processor->_initsFrec[_subscriber].end(),_procesables);
			_processor->addCommand(new CommandTimedSubscribeUpdate(SubscriptionLevel::Init));
			break;
		}
	}
	return COMMAND_FINAL;
}

CommandAddSubscriptions::~CommandAddSubscriptions() {
}

*/