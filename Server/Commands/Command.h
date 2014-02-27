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
#define COMMAND_FINAL 0
#define COMMAND_CONTINUE 1
class Processable;
class Command {
public:
	Command(Processor* processor, uint32_t time);
	uint32_t getTime(){return _time;}
	virtual uint32_t execute(){}
	virtual ~Command();
private:
	uint32_t _time;
	Processor* _processor;
};

#endif	/* COMMAND_H */

