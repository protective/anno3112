/* 
 * File:   CommandAddSubscriptions.h
 * Author: karsten
 *
 * Created on 4. marts 2014, 22:15
 */

#ifndef COMMANDADDSUBSCRIPTIONS_H
#define	COMMANDADDSUBSCRIPTIONS_H

#include "Command.h"

class Processor;
class CommandAddSubscriptions : public Command {
public:
	CommandAddSubscriptions(Processor* subscriber, SubscriptionLevel::Enum level, list<uint32_t> procesables);
	CommandAddSubscriptions(Processor* subscriber, SubscriptionLevel::Enum level, uint32_t procesables);
	virtual uint32_t execute();
	virtual ~CommandAddSubscriptions();
private:
	Processor* _subscriber;
	SubscriptionLevel::Enum _level;
	list<uint32_t> _procesables;
};

#endif	/* COMMANDADDSUBSCRIPTIONS_H */

