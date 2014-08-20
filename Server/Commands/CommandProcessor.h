/* 
 * File:   CommandProcessor.h
 * Author: karsten
 *
 * Created on 9. marts 2014, 12:59
 */

#ifndef COMMANDPROCESSOR_H
#define	COMMANDPROCESSOR_H


#include "Command.h"

class CommandProcessor : public Command  {
public:
	CommandProcessor(Processable* processable, uint32_t interval, uint32_t first);
	virtual uint32_t execute();
	virtual Processable* getProcessable(){return _processable;}
	virtual ~CommandProcessor();
private:
	Processable* _processable;
	uint32_t _interval;
	uint32_t _lastExecuteTime;
};

#endif	/* COMMANDPROCESSOR_H */

