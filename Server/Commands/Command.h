/* 
 * File:   Command.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 21:00
 */

#ifndef COMMAND_H
#define	COMMAND_H
#include "../SFunctions.h"
#include "Processor.h"

class Processable;
class Command {
public:
	Command(Processable* obj);
	uint32_t getTime(){return _time;}
	virtual uint32_t execute(){}
	virtual ~Command();
private:
	uint32_t _time;
	Processable* _obj;
};

#endif	/* COMMAND_H */

