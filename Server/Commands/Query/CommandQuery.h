/* 
 * File:   CommandQuery.h
 * Author: karsten
 *
 * Created on 26. september 2014, 17:56
 */

#ifndef COMMANDQUERY_H
#define	COMMANDQUERY_H

#include "../Command.h"
#include "CommandQueryTable.h"

class CommandQuery : public Command {
public:
	CommandQuery(OBJID sender, qureyOrderBy _orderby, list<qureyCondition> conditions, uint32_t limit);
	virtual uint32_t execute();
	virtual ~CommandQuery();
private:
	OBJID _sender;
	bool checkCondition(qureyCondition condition, SObj* obj);
	uint32_t getValue(uint32_t attri, SObj* obj);
	qureyOrderBy _orderby;
	list<qureyCondition> _conditions;
	list<uint64_t> _attriRsp;
	uint32_t _limit;
};

#endif	/* COMMANDQUERY_H */

