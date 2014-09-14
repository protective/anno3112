/* 
 * File:   CommandOrderThread.h
 * Author: karsten
 *
 * Created on 4. september 2014, 22:14
 */

#ifndef COMMANDORDERTHREAD_H
#define	COMMANDORDERTHREAD_H

#include "../../Commands/Command.h"
#include "SOrdreProgram.h"
#include "Utils/SOrderVar.h"

#include "SOrdersSystemCalls.h"

class CommandOrderThread : public Command {
public:
	CommandOrderThread(SOrdreProgram* program, OBJID obj);
	virtual Processable* getProcessable(){return NULL;} //TODO FIX
	virtual uint32_t execute();
	virtual ~CommandOrderThread();
private:

	uint32_t _mipsCredit;
	TIME _lastExeTime;
	OBJID _obj;
	
	SOrdreProgram* _program;
	uint32_t _programCounter;
	uint32_t _stackTop;
	//list<SOrderNode*> _programStack;

	uint32_t* _stack;
	
    /*
     */
	
};

#endif	/* COMMANDORDERTHREAD_H */

