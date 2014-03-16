/* 
 * File:   CommandAdd.h
 * Author: karsten
 *
 * Created on 25. februar 2014, 22:44
 */

#ifndef COMMANDADD_H
#define	COMMANDADD_H
#include "../SFunctions.h"
#include "Command.h"

class CommandAdd : public Command {
public:
	CommandAdd(uint32_t time, Processable* obj,list<Command*> commands);
	virtual uint32_t execute(){}
	virtual ~CommandAdd();
protected:
	Processable* _obj;
	list<Command*> _commands;
};

#endif	/* COMMANDADD_H */

