/* 
 * File:   CommandCargoTransMsg.h
 * Author: karsten
 *
 * Created on 25. september 2014, 23:02
 */

#ifndef COMMANDCARGOTRANSMSG_H
#define	COMMANDCARGOTRANSMSG_H
#include "../Command.h"
class CommandCargoTransMsg : public Command   {
public:
	CommandCargoTransMsg(uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan);
	virtual uint32_t execute();
	virtual ~CommandCargoTransMsg();
private:
	uint32_t _fromShipId;
	uint32_t _toShipId;
	uint32_t _itemType;
	uint32_t _quan;
};

#endif	/* COMMANDCARGOTRANSMSG_H */

