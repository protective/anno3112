/* 
 * File:   CommandUpdateMetas.h
 * Author: karsten
 *
 * Created on 4. marts 2014, 22:38
 */

#ifndef COMMANDUPDATEMETAS_H
#define	COMMANDUPDATEMETAS_H
#include "Command.h"
#include "../Sspacebjects/SPos.h"
/*
struct MetaInit{
	MetaInit(){
		vecX = 0;
		vecY = 0;
		vecZ = 0;

	}

	uint32_t id;
	uint8_t team;
	uint32_t size;
	TargetType::Enum targetType;
	SpaceTypes::Enum type;
	SPos pos;
	uint32_t scan, scanP;
	uint8_t procesNodeId;
	int32_t vecX, vecY, vecZ;
	
	MetaInit(const MetaInit& m){
		id = m.id;
		pos = m.pos;
		scan = m.scan;
		scanP = m.scanP;
		procesNodeId = m.procesNodeId;
		team = m.team;
		size = m.size;
		targetType = m.targetType;
		type = m.type;
		vecX = m.vecX;
		vecY = m.vecY;
		vecZ = m.vecZ;
	}
};

struct MetaRemove{
	MetaRemove(){}
	uint32_t id;
	MetaRemove(const MetaInit& m){
		id = m.id;

	}
};

struct MetaLow{
	MetaLow(){
		vecX = 0;
		vecY = 0;
		vecZ = 0;
	}

	uint32_t id;
	SPos pos;
	uint32_t scan, scanP;
	uint8_t procesNodeId;
	int32_t vecX, vecY, vecZ;
	
	MetaLow(const MetaLow& m){
		id = m.id;
		pos = m.pos;
		vecX = m.vecX;
		vecY = m.vecY;
		vecZ = m.vecZ;
		scan = m.scan;
		scanP = m.scanP;
		procesNodeId = m.procesNodeId;
	}
};

class CommandUpdateMetas : public Command {
public:
	CommandUpdateMetas(uint8_t freq, list<MetaLow> objToSend);
	CommandUpdateMetas(uint8_t freq, list<MetaInit> objToSend);
	CommandUpdateMetas(uint8_t freq, list<MetaRemove> objToSend);
	virtual uint32_t execute();
	virtual ~CommandUpdateMetas();
private:

	uint8_t _freq;
	list<MetaInit> _objToSendInit;
	list<MetaRemove> _objToSendRemove;
	list<MetaLow> _objToSendLow;
};
*/
#endif	/* COMMANDUPDATEMETAS_H */

