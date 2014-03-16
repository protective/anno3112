/* 
 * File:   CommandTransfere.h
 * Author: karsten
 *
 * Created on 25. februar 2014, 23:17
 */

#ifndef COMMANDTRANSFERE_H
#define	COMMANDTRANSFERE_H
#include "../SFunctions.h"
#include "Command.h"

class CommandTransfere : public Command {
public:
	CommandTransfere(uint32_t time, Processor* toProcessor, Processable* toTransfere);
	virtual uint32_t execute();
	virtual ~CommandTransfere();
private:
	Processable* _toTransfere;
	Processor* _toProcessor;
};

#endif	/* COMMANDTRANSFERE_H */

