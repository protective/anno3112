/* 
 * File:   CommandHit.h
 * Author: karsten
 *
 * Created on 1. juni 2014, 22:27
 */

#ifndef COMMANDHIT_H
#define	COMMANDHIT_H

#include "../SFunctions.h"
#include "Command.h"

class CommandHit : public Command{
public:
	CommandHit(uint32_t target, uint32_t shot, uint32_t dmg, DmgTypes::Enum dmgType, Shields::Enum impact, int32_t x, int32_t y);
	virtual uint32_t execute();
	virtual ~CommandHit();
protected:
	uint32_t _target;
	uint32_t _shot;
	uint32_t _dmg;
	DmgTypes::Enum _dmgType;
	Shields::Enum _impact;
	int32_t _x;
	int32_t _y;
};

#endif	/* COMMANDHIT_H */

