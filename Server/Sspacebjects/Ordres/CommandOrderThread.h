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

class CommandOrderThread : public Command {
public:
	CommandOrderThread(OBJID obj);
	virtual Processable* getProcessable(){return NULL;} //TODO FIX
	virtual uint32_t execute();
	virtual ~CommandOrderThread();
private:

	OBJID _procesable;

	
};

#endif	/* COMMANDORDERTHREAD_H */

