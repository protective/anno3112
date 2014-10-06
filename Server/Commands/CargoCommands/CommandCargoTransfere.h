/* 
 * File:   CommandCargoTransfere.h
 * Author: karsten
 *
 * Created on 1. oktober 2014, 23:05
 */

#ifndef COMMANDCARGOTRANSFERE_H
#define	COMMANDCARGOTRANSFERE_H
#include "../Command.h"

class CommandCargoTransfere : public Command {
public:
	CommandCargoTransfere(uint32_t fromShipId, uint32_t toShipId, uint32_t itemType, uint32_t quan);
	virtual uint32_t execute();
	virtual ~CommandCargoTransfere();
private:
	uint32_t _fromShipId;
	uint32_t _toShipId;
	uint32_t _itemType;
	uint32_t _quan;
};

#endif	/* COMMANDCARGOTRANSFERE_H */

