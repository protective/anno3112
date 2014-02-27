/* 
 * File:   Processable.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 22:25
 */

#include "Processable.h"
#include "../World/SWorld.h"

Processable::Processable(uint32_t id) {
	this->_id = id;
}

uint32_t Processable::addCommand(Command* cmd){
	if(_processor)
		_processor->addCommand(cmd);
			
}
uint32_t Processable::removeCommand(Command* cmd){
	if(_processor)
		_processor->removeCommand(cmd);
}

Processable::~Processable() {
}

