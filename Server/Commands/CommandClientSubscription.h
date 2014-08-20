/* 
 * File:   CommandClientSubscription.h
 * Author: karsten
 *
 * Created on 17. april 2014, 09:36
 */

#ifndef COMMANDCLIENTSUBSCRIPTION_H
#define	COMMANDCLIENTSUBSCRIPTION_H
#include "../SFunctions.h"
#include "Command.h"


class CommandClientSubscription : public Command {
public:
	CommandClientSubscription(uint32_t time, uint32_t client, uint32_t target, SubscriptionLevel::Enum level);
	virtual uint32_t execute();
	virtual ~CommandClientSubscription();
private:
	uint32_t _client;
	uint32_t _target;
	SubscriptionLevel::Enum _level;
};

#endif	/* COMMANDCLIENTSUBSCRIPTION_H */

