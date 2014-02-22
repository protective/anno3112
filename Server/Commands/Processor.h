/* 
 * File:   Processor.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 22:24
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

#include "../SFunctions.h"
#include "Command.h"


class Processor {
public:
	Processor();
	
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);
	
	
	static void* workThreadFunction(void* context);
	
	virtual ~Processor();
private:
	void work();
	Command* procesFirstReadyCommand();
	
	pthread_mutex_t _lockCommands; //protect the command list
	pthread_cond_t _workCond;   //workReady condition
	pthread_mutex_t _workMutex; //protect the workReady signal
	bool _workReady;
	
	list<Command*> _commands;
		
	map<uint32_t, Processable*> _localObjects;
	
};

#endif	/* PROCESSOR_H */

