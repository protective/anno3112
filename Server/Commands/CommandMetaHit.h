/* 
 * File:   CommandMetaHit.h
 * Author: karsten
 *
 * Created on 17. juli 2014, 16:14
 */

#ifndef COMMANDMETAHIT_H
#define	COMMANDMETAHIT_H

#include "Command.h"


class CommandMetaHit : public Command {
public:
	CommandMetaHit(uint32_t shot, uint32_t target, Shields::Enum shield, int32_t x, int32_t y);
	//svirtual Processable* getProcessable(){return _;}

	virtual uint32_t execute();
	virtual ~CommandMetaHit();
private:
	uint32_t _shot;
	uint32_t _target;
	Shields::Enum _shield;
	int32_t _x;
	int32_t _y;
};

#endif	/* COMMANDMETAHIT_H */

