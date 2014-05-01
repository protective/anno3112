/* 
 * File:   Processable.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 22:25
 */

#include "Processable.h"
#include "../World/SWorld.h"

Processable::Processable() {
	_processor = NULL;
}

uint32_t Processable::addCommand(Command* cmd){
	if(_processor){
		_processor->addCommand(cmd);
	}else{
		_localQueue.push_back(cmd);
	}
			
}
uint32_t Processable::removeCommand(Command* cmd){
	if(_processor)
		_processor->removeCommand(cmd);
}

Processable::~Processable() {
}

