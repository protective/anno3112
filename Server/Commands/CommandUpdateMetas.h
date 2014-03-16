/* 
 * File:   CommandUpdateMetas.h
 * Author: karsten
 *
 * Created on 4. marts 2014, 22:38
 */

#ifndef COMMANDUPDATEMETAS_H
#define	COMMANDUPDATEMETAS_H
#include "Command.h"

struct MetaLow{
	uint32_t id;
	SPos pos;
	uint32_t scan, scanP;
	uint8_t procesNodeId;
};

class CommandUpdateMetas : public Command {
public:
	CommandUpdateMetas(uint8_t freq, list<MetaLow> objToSend);
	virtual uint32_t execute();
	virtual ~CommandUpdateMetas();
private:

	uint8_t _freq;
	list<MetaLow> _objToSend;
};

#endif	/* COMMANDUPDATEMETAS_H */

