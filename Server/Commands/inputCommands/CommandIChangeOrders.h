/* 
 * File:   CommandIChangeOrders.h
 * Author: karsten
 *
 * Created on 15. august 2014, 23:54
 */

#ifndef COMMANDICHANGEORDERS_H
#define	COMMANDICHANGEORDERS_H
#include "../Command.h"
class CommandIChangeOrders : public Command {
public:

	CommandIChangeOrders(uint32_t shipId, uint32_t ordreId,  uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandIChangeOrders();
private:
	uint32_t _shipId;
	uint32_t _ordreId;
	uint32_t _clientId;
};

#endif	/* COMMANDICHANGEORDERS_H */

