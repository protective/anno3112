/* 
 * File:   CommandTimedSubscribeUpdate.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:32
 */

#include "CommandTimedSubscribeUpdate.h"
#include "CommandUpdateMetas.h"
#include "../Sspacebjects/SMetaObj.h"
#include "../Sspacebjects/SUnit.h"

#include "../World/SWorld.h"
CommandTimedSubscribeUpdate::CommandTimedSubscribeUpdate(SubscriptionLevel::Enum freq):
Command(0) {
	_freq = freq;
}

uint32_t CommandTimedSubscribeUpdate::execute(){
	//cerr<<"execure CommandTimedSubscribeUpdate freq="<<_freq<<endl;
	switch(_freq){
		case SubscriptionLevel::lowFreq:{
			for(map<Processor*, list<uint32_t> >::iterator it = _processor->_lowFrec.begin(); it != _processor->_lowFrec.end(); it++){
				list<MetaLow> templist;
				for(list<uint32_t>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
					MetaLow temp;
					
					SObj* obj = NULL;
					obj = (_processor->_localObjects.find(*it2) != _processor->_localObjects.end() ? _processor->_localObjects[*it2]->isObj(): NULL);
					
					if(obj && (obj->isUnit() || obj->isShot())){
						temp.id =  *it2;
						temp.pos = obj->getPos();
						if(obj->isMovable()){
							temp.vecX = obj->isMovable()->getMoveX();
							temp.vecY = obj->isMovable()->getMoveY();
							temp.vecZ = obj->isMovable()->getMoveZ();
						}
						temp.procesNodeId = _processor->getId();
						if(obj->isUnit()){
							temp.scan = obj->isUnit()->getScanRange();
							temp.scanP = obj->isUnit()->getScanRange();
						}
						//cerr<<"send id="<<*it2<<endl;
						templist.push_back(temp);
					}
				}
				it->first->addCommand(new CommandUpdateMetas(1,templist));
			}
			_time += 5000;
			break;
		}
		case SubscriptionLevel::Init:{
			for(map<Processor*, list<uint32_t> >::iterator it = _processor->_initsFrec.begin(); it != _processor->_initsFrec.end(); it++){
				list<MetaInit> templist;
				for(list<uint32_t>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
					MetaInit temp;
					SObj* obj = NULL;
					if(_processor->_localObjects.find(*it2) != _processor->_localObjects.end()){
						if(_processor->_localObjects[*it2]->isUnit() || _processor->_localObjects[*it2]->isShot())
							obj = _processor->_localObjects[*it2]->isObj();
						
					}
					if(obj){
						temp.id =  *it2;
						if(obj->isShip())
							temp.type =  SpaceTypes::Ship;
						if(obj->isFighter()){
							temp.type =  SpaceTypes::Fighter;
							cerr<<"FIGHTER"<<endl;
						}
						if(obj->isShot())
							temp.type =  SpaceTypes::Shot;
						if(obj->isAstoroid())
							temp.type =  SpaceTypes::Astoroid;
						temp.team = obj->getTeam();
						temp.size = obj->getSize();
						temp.targetType = obj->isTargetable() ? obj->isTargetable()->getTargetType() : TargetType::Invalid;
						temp.pos = obj->getPos();
						if(obj->isMovable()){
							temp.vecX = obj->isMovable()->getMoveX();
							temp.vecY = obj->isMovable()->getMoveY();
							temp.vecZ = obj->isMovable()->getMoveZ();
						}
						temp.procesNodeId = _processor->getId();
						if(obj->isUnit()){
							temp.scan = obj->isUnit()->getScanRange();
							temp.scanP = obj->isUnit()->getScanRange();
						}
						
						templist.push_back(temp);
					}
				}
				it->first->addCommand(new CommandUpdateMetas(1,templist));
			}
			_processor->_initsFrec.clear();
			return COMMAND_FINAL;
		}
	}
	
	//_processor->addCommand(this);
	return COMMAND_REPEAT;
}

CommandTimedSubscribeUpdate::~CommandTimedSubscribeUpdate() {
}

