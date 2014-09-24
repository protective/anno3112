/* 
 * File:   CommandQueryCmp.h
 * Author: karsten
 *
 * Created on 24. september 2014, 19:26
 */

#ifndef COMMANDQUERYCMP_H
#define	COMMANDQUERYCMP_H

#include "Command.h"


class CommandQueryCmp  : public Command {
public:
	CommandQueryCmp(OBJID programmable);
	virtual uint32_t execute();
	virtual ~CommandQueryCmp();
private:
	OBJID _procesable;
	uint32_t _callbackProgramID;
	uint32_t _callbackHandler;
	uint32_t* _payload;
};

#endif	/* COMMANDQUERYCMP_H */

