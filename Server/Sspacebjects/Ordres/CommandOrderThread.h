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
typedef void (*systemCall)(Processor*, void*);

void systemSetSubsystemFlags(void* arg){}

class CommandOrderThread : public Command {
public:
	CommandOrderThread(SOrdreProgram* program, OBJID obj);
	virtual Processable* getProcessable(){return NULL;} //TODO FIX
	virtual uint32_t execute();
	void pushStack(SOrderVar* var){
		_stack.push_back(var);
	}
	virtual ~CommandOrderThread();
private:

	uint32_t _mipsCredit;
	TIME _lastExeTime;
	OBJID _obj;
	SOrdreProgram* _program;
	uint32_t _programCounter;
	//list<SOrderNode*> _programStack;
	vector<SOrderVar*> _stack;
	

	vector<systemCall> _systemCalls;
    /*
     */
	
};

#endif	/* COMMANDORDERTHREAD_H */

