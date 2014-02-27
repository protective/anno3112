/* 
 * File:   Command.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 21:00
 */

#include "Command.h"

Command::Command(Processor* processor, uint32_t time) {
	_time = time;
	_processor = processor;
}

Command::~Command() {
}

