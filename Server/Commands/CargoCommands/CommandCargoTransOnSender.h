/* 
 * File:   CommandCargoTransOnSender.h
 * Author: karsten
 *
 * Created on 25. september 2014, 23:02
 */

#ifndef COMMANDCARGOTRANSONSENDER_H
#define	COMMANDCARGOTRANSONSENDER_H
#include "../Command.h"
class CommandCargoTransOnSender : public Command   {
public:
	CommandCargoTransOnSender(uint32_t id, uint32_t fromShipId, uint32_t toShipId, uint32_t retMsg, uint32_t quan);
	virtual uint32_t execute();
	virtual ~CommandCargoTransOnSender();
private:
	uint32_t _id;
	uint32_t _fromShipId;
	uint32_t _toShipId;
	uint32_t _retmsg;
	uint32_t _quan;
};

#endif	/* COMMANDCARGOTRANSONSENDER_H */

