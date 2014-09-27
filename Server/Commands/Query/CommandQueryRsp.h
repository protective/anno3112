/* 
 * File:   CommandQueryRsp.h
 * Author: karsten
 *
 * Created on 26. september 2014, 17:57
 */

#ifndef COMMANDQUERYRSP_H
#define	COMMANDQUERYRSP_H

#include "../Command.h"
#include "CommandQueryTable.h"


class CommandQueryRsp : public Command {
public:
	CommandQueryRsp(OBJID _reciver, list<qureyRow> _rspData);
	virtual uint32_t execute();
	virtual ~CommandQueryRsp();
private:
	OBJID _reciver;
	list<qureyRow> _rspData;
};

#endif	/* COMMANDQUERYRSP_H */

