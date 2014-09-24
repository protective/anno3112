/* 
 * File:   SOrdreProgram.cpp
 * Author: karsten
 * 
 * Created on 5. september 2014, 17:48
 */

#include "SOrdreProgram.h"

SOrdreProgram::SOrdreProgram(string name, PROGRAM program, map<uint32_t, uint32_t> interruptHandlers){
	_name = name;
	_program = program;
	_interruptHandlers = interruptHandlers;
}


SOrdreProgram::~SOrdreProgram() {
}

