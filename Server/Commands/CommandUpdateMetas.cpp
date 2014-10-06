/* 
 * File:   CommandUpdateMetas.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:38
 */

#include "CommandUpdateMetas.h"
#include "../World/SWorld.h"
#include "../Sspacebjects/SMetaShot.h"
CommandUpdateMetas::CommandUpdateMetas(uint8_t freq, list<MetaLow> objToSend):
Command(world->getTime()){
	_freq = freq;
	_objToSendLow = objToSend;

}

CommandUpdateMetas::CommandUpdateMetas(uint8_t freq, list<MetaInit> objToSend):
Command(world->getTime()){
	_freq = freq;
	_objToSendInit = objToSend;

}

CommandUpdateMetas::CommandUpdateMetas(uint8_t freq, list<MetaRemove> objToSend):
Command(world->getTime()){
	_freq = freq;
	_objToSendRemove = objToSend;
}

uint32_t CommandUpdateMetas::execute(){
	//cerr<<"execure CommandUpdateMetas"<<endl;

	for(list<MetaLow>::iterator it = _objToSendLow.begin(); it != _objToSendLow.end();it++){
		if(_processor->_metaObjs.find(it->id) == _processor->_metaObjs.end())
		{
			//cerr<<"ERROR Meta not found"<<endl;
			continue;
		}
		//cerr<<"update low id="<<it->id<<endl;
		_processor->_metaObjs[it->id]->pos = it->pos;
		_processor->_metaObjs[it->id]->vecX = it->vecX;
		_processor->_metaObjs[it->id]->vecY = it->vecY;
		_processor->_metaObjs[it->id]->vecZ = it->vecZ;
		_processor->_metaObjs[it->id]->scan = it->scan;
		_processor->_metaObjs[it->id]->scanP = it->scanP;
		_processor->_metaObjs[it->id]->procesNodeId = it->procesNodeId;
		_processor->_metaObjs[it->id]->_timerLowFeq = world->getTime();
	}
	for(list<MetaInit>::iterator it = _objToSendInit.begin(); it != _objToSendInit.end();it++){
		if(_processor->_metaObjs.find(it->id) == _processor->_metaObjs.end())
			_processor->_metaObjs[it->id] = it->type != SpaceTypes::Shot ? new SMetaObj(it->id) : new SMetaShot(it->id);
		_processor->_metaObjs[it->id]->team = it->team;
		_processor->_metaObjs[it->id]->targetType = it->targetType;
		_processor->_metaObjs[it->id]->_size = it->size;
		_processor->_metaObjs[it->id]->pos = it->pos;
		_processor->_metaObjs[it->id]->vecX = it->vecX;
		_processor->_metaObjs[it->id]->vecY = it->vecY;
		_processor->_metaObjs[it->id]->vecZ = it->vecZ;
		
		_processor->_metaObjs[it->id]->scan = it->scan;
		_processor->_metaObjs[it->id]->scanP = it->scanP;
		_processor->_metaObjs[it->id]->procesNodeId = it->procesNodeId;
		_processor->_metaObjs[it->id]->_timerLowFeq = world->getTime();
	}
	
	for(list<MetaRemove>::iterator it = _objToSendRemove.begin(); it != _objToSendRemove.end();it++){
		if(_processor->_metaObjs.find(it->id) != _processor->_metaObjs.end()){
			//cerr<<"DELETE META id ="<<it->id<<endl;
			delete _processor->_metaObjs[it->id];
			_processor->_metaObjs.erase(it->id);
		}
		//cerr<<"NOT FOUND META id ="<<it->id<<endl;
	}
	//cerr<<"done execure CommandUpdateMetas"<<endl;
	return COMMAND_FINAL;
}

CommandUpdateMetas::~CommandUpdateMetas() {
}

