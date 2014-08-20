/* 
 * File:   Command.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 21:00
 */

#ifndef COMMAND_H
#define	COMMAND_H
#include "../SFunctions.h"

#define COMMAND_FINAL 0
#define COMMAND_CONTINUE 1
#define COMMAND_REPEAT 2

class Processor;
class Processable;
class Command {
public:
	Command(uint32_t time);
	uint32_t getTime(){return _time;}
	Processor* getProcessor(){return _processor ;}
	void setProcessor(Processor* processor){_processor = processor;}
	virtual Processable* getProcessable(){return NULL;}
	virtual uint32_t execute(){}
	virtual void serialize(){}
	virtual ~Command();
protected:
	uint32_t _time;
	Processor* _processor;
};

#endif	/* COMMAND_H */

