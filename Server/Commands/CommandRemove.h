/* 
 * File:   CommandRemove.h
 * Author: karsten
 *
 * Created on 9. maj 2014, 23:36
 */

#ifndef COMMANDREMOVE_H
#define	COMMANDREMOVE_H

#include "../SFunctions.h"
#include "Command.h"

class CommandRemove : public Command {
public:
	CommandRemove(uint32_t time, Processable* processable);
	virtual Processable* getProcessable(){return _processable;}
	virtual uint32_t execute();
	virtual ~CommandRemove();
private:
	Processable* _processable;
};

#endif	/* COMMANDREMOVE_H */

