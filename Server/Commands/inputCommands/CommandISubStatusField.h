/* 
 * File:   CommandISubStatusField.h
 * Author: karsten
 *
 * Created on 26. april 2014, 16:59
 */

#ifndef COMMANDISUBSTATUSFIELD_H
#define	COMMANDISUBSTATUSFIELD_H
#include "../Command.h"
class CommandISubStatusField : public Command {
public:
	CommandISubStatusField(uint32_t shipId, uint32_t subId, uint32_t statusField, uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandISubStatusField();
private:
	uint32_t _shipId;
	uint32_t _subId;
	uint32_t _statusField;
	uint32_t _clientId;
};

#endif	/* COMMANDISUBSTATUSFIELD_H */

