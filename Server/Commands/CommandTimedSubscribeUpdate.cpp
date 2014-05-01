/* 
 * File:   CommandTimedSubscribeUpdate.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:32
 */

#include "CommandTimedSubscribeUpdate.h"
#include "CommandUpdateMetas.h"
#include "../Sspacebjects/SMetaObj.h"
#include "../World/SWorld.h"
CommandTimedSubscribeUpdate::CommandTimedSubscribeUpdate(uint8_t freq):
Command(0) {
	_freq = freq;
}

uint32_t CommandTimedSubscribeUpdate::execute(){
	cerr<<"execure CommandTimedSubscribeUpdate"<<endl;
	switch(_freq){
		case 1:{
			for(map<Processor*, list<uint32_t> >::iterator it = _processor->_lowFrec.begin(); it != _processor->_lowFrec.end(); it++){
				cerr<<"hest1"<<endl;
				list<MetaLow> templist;
				for(list<uint32_t>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
					MetaLow temp;
					cerr<<"hest2"<<endl;
					SObj* obj = NULL;
					if(obj = (_processor->_localObjects.find(*it2) != _processor->_localObjects.end() ? _processor->_localObjects[*it2]->isUnit(): NULL)){
						cerr<<"hest22"<<endl;
						temp.id =  *it2;
						temp.pos = obj->getPos();
						cerr<<"setpos "<<temp.pos.x<<","<<temp.pos.y<<endl;
						cerr<<"hest3"<<endl;
						temp.procesNodeId = _processor->getId();
						if(obj->isUnit()){
							cerr<<"hest33"<<endl;
							temp.scan = obj->isUnit()->getScanRange();
							temp.scanP = obj->isUnit()->getScanRange();
						}
						cerr<<"hest4"<<endl;
						templist.push_back(temp);
					}

				}
				cerr<<"hest5"<<endl;
				for(list<MetaLow>::iterator it2 = templist.begin(); it2 != templist.end();it2++){
					cerr<<"id="<<it2->id<<endl;
					cerr<<"before pos="<<it2->pos.x<<","<<it2->pos.y<<endl;
				}
				it->first->addCommand(new CommandUpdateMetas(1,templist));
			}
			cerr<<"hest6"<<endl;
			_time += 5000;
			break;
		}
	}
	_processor->addCommand(this);
	return COMMAND_CONTINUE;
}

CommandTimedSubscribeUpdate::~CommandTimedSubscribeUpdate() {
}

