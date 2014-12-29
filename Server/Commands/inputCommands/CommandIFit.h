/* 
 * File:   CommandIFit.h
 * Author: karsten
 *
 * Created on 26. april 2014, 17:02
 */

#ifndef COMMANDIFIT_H
#define	COMMANDIFIT_H

#include "../Command.h"
class CommandIFit : public Command {
public:
	CommandIFit(uint32_t fromId, uint32_t subid, uint32_t toId, uint32_t quantity,uint32_t itemid,  uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandIFit();
private:
	uint32_t _step;
	uint32_t _fromId;
	uint32_t _subid;
	uint32_t _toId;
	uint32_t _quantity;
	uint32_t _itemId;
	uint32_t _clientId;
};

#endif	/* COMMANDIFIT_H */

