/* 
 * File:   CommandTargetPosUpdate.h
 * Author: karsten
 *
 * Created on 22. april 2014, 23:25
 */

#ifndef COMMANDTARGETPOSUPDATE_H
#define	COMMANDTARGETPOSUPDATE_H

#include "Command.h"


class CommandTargetPosUpdate : public Command {
public:
	CommandTargetPosUpdate(uint32_t time, SerialPCShipTargetPosUpdate* message, uint32_t clientId);
	virtual uint32_t execute();
	virtual ~CommandTargetPosUpdate();
private:
	SerialPCShipTargetPosUpdate* _message;;
	uint32_t _clientId;
};

#endif	/* COMMANDTARGETPOSUPDATE_H */

