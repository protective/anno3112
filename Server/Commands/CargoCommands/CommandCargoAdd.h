/* 
 * File:   CommandCargoAdd.h
 * Author: karsten
 *
 * Created on 5. oktober 2014, 21:24
 */

#ifndef COMMANDCARGOADD_H
#define	COMMANDCARGOADD_H
#include "../Command.h"

class CommandCargoAdd : public Command {
public:
	CommandCargoAdd(uint32_t toShipId, uint32_t itemType, uint32_t quan);
	virtual uint32_t execute();
	virtual ~CommandCargoAdd();
private:
	uint32_t _toShipId;
	uint32_t _itemType;
	uint32_t _quan;
};

#endif	/* COMMANDCARGOADD_H */

