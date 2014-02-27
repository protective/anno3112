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
	map<uint32_t, Processable*>& getLocalProcssable(){return _localObjects;}
	uint32_t getFreeID();
	
	virtual ~Processor();
private:
	
	//Command processing
	void work();
	Command* procesFirstReadyCommand();
	pthread_mutex_t _lockCommands; //protect the command list
	pthread_cond_t _workCond;   //workReady condition
	pthread_mutex_t _workMutex; //protect the workReady signal
	bool _workReady;
	list<Command*> _commands;
	
	//processor Data
	uint8_t _id;
	uint32_t _freeIdCount;
	pthread_mutex_t _lockFreeID;
	map<uint32_t, Processable*> _localObjects;
	
	map<uint32_t, SMetaObj*> _metaObjs;
	
};

#endif	/* PROCESSOR_H */

