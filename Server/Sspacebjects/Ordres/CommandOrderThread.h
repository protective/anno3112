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

#include "SOrdersSystemCalls.h"
namespace registerFlags{
	enum Enum{
		Yeld = 0x00000001
	};
}
class CommandOrderThread : public Command {
public:
	CommandOrderThread(SOrdreProgram* program, OBJID obj);
	virtual Processable* getProcessable(){return NULL;} //TODO FIX
	virtual uint32_t execute();
	void sleep(uint32_t ms);
	virtual ~CommandOrderThread();
private:
	uint32_t segfault();
	void dumpStack();
	uint32_t _registerFlags;
	uint32_t _mipsCredit;
	TIME _lastExeTime;
	OBJID _obj;
	
	SOrdreProgram* _program;
	uint32_t _programCounter;
	uint32_t _stackTop;
	//list<SOrderNode*> _programStack;

	uint32_t* _stack;
	uint32_t _stackMax;
    /*
     */
	
};

#endif	/* COMMANDORDERTHREAD_H */

