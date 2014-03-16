/* 
 * File:   CommandTimedSubscribeUpdate.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:32
 */

#include "CommandTimedSubscribeUpdate.h"
#include "CommandUpdateMetas.h"

CommandTimedSubscribeUpdate::CommandTimedSubscribeUpdate(uint8_t freq):
Command(world->getTime()) {
	_freq = freq;
}

uint32_t CommandTimedSubscribeUpdate::execute(){
	
	switch(_freq){
		case 1:{
			for(map<Processor*, list<uint32_t> >::iterator it = _processor->_lowFrec.begin(); it != _processor->_lowFrec.end(); it++){
				
				list<MetaLow> templist;
				for(list<uint32_t>::iterator it2 = it->second.begin(); it != it->second.end(); it2++){
					MetaLow temp;
					temp.id =  *it2;
					temp.pos = _processor->_metaObjs[*it2].pos;
					temp.procesNodeId = _processor->_metaObjs[*it2].procesNodeId;
					temp.scan = _processor->_metaObjs[*it2].scan;
					temp.scanP = _processor->_metaObjs[*it2].scanP;
					templist.push_back(temp);
				}
				it->first->addCommand(new CommandUpdateMetas(1,templist));
			}
			
			_time += 5000;
			break;
		}
	}
	_processor->addCommand(this);
	return COMMAND_CONTINUE
}

CommandTimedSubscribeUpdate::~CommandTimedSubscribeUpdate() {
}

