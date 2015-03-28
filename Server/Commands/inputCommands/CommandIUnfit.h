/* 
 * File:   CommandIUnfit.h
 * Author: karsten
 *
 * Created on 26. april 2014, 17:01
 */

#ifndef COMMANDIUNFIT_H
#define	COMMANDIUNFIT_H
#include "../Command.h"
class CommandIUnfit : public Command {
public:
	CommandIUnfit(uint32_t fromId, uint32_t subid, uint32_t toId, uint32_t quantity, uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandIUnfit();
private:
	uint32_t _step;
	uint32_t _fromId;
	uint32_t _toId;
	uint32_t _itemId;
	uint32_t _subid;
	uint32_t _quantity;
	uint32_t _clientId;
};

#endif	/* COMMANDIUNFIT_H */

