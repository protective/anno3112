/* 
 * File:   Command.cpp
 * Author: karsten
 * 
 * Created on 16. februar 2014, 21:00
 */

#include "Command.h"

Command::Command(Processable* obj) {
	_obj = obj;
}

Command::~Command() {
}

