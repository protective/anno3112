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
	CommandTransfere(Processor* processor, Processable* obj);
	virtual ~CommandTransfere();
private:

};

#endif	/* COMMANDTRANSFERE_H */

