/* 
 * File:   CommandTimedSubscribeUpdate.h
 * Author: karsten
 *
 * Created on 4. marts 2014, 22:32
 */

#ifndef COMMANDTIMEDSUBSCRIBEUPDATE_H
#define	COMMANDTIMEDSUBSCRIBEUPDATE_H
#include "Command.h"

class CommandTimedSubscribeUpdate : public Command{
public:
	CommandTimedSubscribeUpdate(SubscriptionLevel::Enum freq);
	virtual uint32_t execute();
	virtual ~CommandTimedSubscribeUpdate();
private:
	SubscriptionLevel::Enum _freq;
};

#endif	/* COMMANDTIMEDSUBSCRIBEUPDATE_H */

