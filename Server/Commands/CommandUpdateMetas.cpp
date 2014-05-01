/* 
 * File:   CommandUpdateMetas.cpp
 * Author: karsten
 * 
 * Created on 4. marts 2014, 22:38
 */

#include "CommandUpdateMetas.h"
#include "../World/SWorld.h"
#include "../Sspacebjects/SMetaObj.h"
CommandUpdateMetas::CommandUpdateMetas(uint8_t freq, list<MetaLow> objToSend):
Command(world->getTime()){
	_freq = freq;
	_objToSend = objToSend;
	for(list<MetaLow>::iterator it = objToSend.begin(); it != objToSend.end();it++){
		cerr<<"id="<<it->id<<endl;
		cerr<<"new pos="<<it->pos.x<<","<<it->pos.y<<endl;
	}
	cerr<<"meta="<<&_objToSend<<endl;
	cerr<<"param="<<&objToSend<<endl;
}

uint32_t CommandUpdateMetas::execute(){
	cerr<<"execure CommandUpdateMetas"<<endl;

	for(list<MetaLow>::iterator it = _objToSend.begin(); it != _objToSend.end();it++){
		if(_processor->_metaObjs.find(it->id) == _processor->_metaObjs.end())
			_processor->_metaObjs[it->id] = new SMetaObj();
		cerr<<"id="<<it->id<<endl;
		cerr<<"pos="<<it->pos.x<<","<<it->pos.y<<endl;
		_processor->_metaObjs[it->id]->pos = it->pos;
		_processor->_metaObjs[it->id]->scan = it->scan;
		_processor->_metaObjs[it->id]->scanP = it->scanP;
		_processor->_metaObjs[it->id]->procesNodeId = it->procesNodeId;
	}
	cerr<<"done execure CommandUpdateMetas"<<endl;
	return COMMAND_FINAL;
}

CommandUpdateMetas::~CommandUpdateMetas() {
}

