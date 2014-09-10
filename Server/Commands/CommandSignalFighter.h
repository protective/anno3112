/* 
 * File:   CommandSignalFighter.h
 * Author: karsten
 *
 * Created on 28. august 2014, 22:13
 */

#ifndef COMMANDSIGNALFIGHTER_H
#define	COMMANDSIGNALFIGHTER_H

#include "Command.h"

class CommandSignalFighter : public Command  {
public:
	CommandSignalFighter(OBJID toId, OBJID fighter, FighterSignal::Enum signal, uint32_t signalParam);
	virtual uint32_t execute();
	virtual ~CommandSignalFighter();
private:
	OBJID _toId;
	OBJID _fighterId;
	FighterSignal::Enum _signal;
	uint32_t _signalParam;
};

#endif	/* COMMANDSIGNALFIGHTER_H */

