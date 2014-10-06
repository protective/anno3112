/* 
 * File:   CommandCargoTransOnReciver.h
 * Author: karsten
 *
 * Created on 25. september 2014, 23:01
 */

#ifndef COMMANDCARGOTRANSONRECIVER_H
#define	COMMANDCARGOTRANSONRECIVER_H
#include "../Command.h"
class CommandCargoTransOnReciver : public Command {
public:
	CommandCargoTransOnReciver(uint32_t id, uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan);
	virtual uint32_t execute();
	virtual ~CommandCargoTransOnReciver();
private:
	uint32_t _id;
	uint32_t _fromShipId;
	uint32_t _toShipId;
	uint32_t _itemType;
	uint32_t _quan;
	
};

#endif	/* COMMANDCARGOTRANSONRECIVER_H */

