/* 
 * File:   Processor.h
 * Author: karsten
 *
 * Created on 16. februar 2014, 22:24
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

#include "../SFunctions.h"
#include "Processable.h"


class SShot;
class SShip;
class SFighter;
class SPos;
class SSubAble;
class STargetable;
class SSubTypeWep;
class SShipType;
class SFighterType;
class SAstoroid;
class SAstoroidType;
class SAstoroidBelt;
class SOrdreProgram;
class Processor {
public:
	friend CommandAddSubscriptions;
	friend CommandTimedSubscribeUpdate;
	friend CommandUpdateMetas;
	friend CommandRemove;
	Processor();
	void init();
	
	uint8_t getId(){return _id;}
	uint32_t addCommand(Command* cmd);
	uint32_t removeCommand(Command* cmd);
	list<Command*> removeByProcessable(Processable* proc);

	static void* workThreadFunction(void* context);
	map<uint32_t, Processable*>& getLocalProcssables(){return _localObjects;}
	Processable* getLocalProcssable(uint32_t obj){return _localObjects.find(obj) != _localObjects.end() ? _localObjects[obj]: NULL;}

	map<uint32_t, SMetaObj*>& getLocalMetas(){return _metaObjs;}
	map<string,SOrdreProgram*>& getPrograms(){return _programs;}
	SOrdreProgram* getProgram(string name);
	SMetaObj* getMeta(uint32_t id){return _metaObjs.find(id) != _metaObjs.end() ? _metaObjs[id] : NULL;}
	uint32_t getFreeID();
	SShot* createShot(SPos& pos, SSubAble* owner, uint32_t target, SSubTypeWep* type);
	SShip* createShip(SPos& pos, SShipType& stype, uint32_t playerId);
	SFighter* createFighter(SPos& pos, SFighterType& ftype, uint32_t playerId, uint32_t mothership, uint32_t motherShipSub);
	SAstoroid* createAsteroid(SPos& pos, SAstoroidType& atype, SAstoroidBelt* belt);
	SAstoroidBelt* createAsteroidBelt(SPos& pos);
	SGrid* createGrid();
	virtual ~Processor();
private:
	
	//Command processing
	void work();
	Command* procesFirstReadyCommand();
	pthread_mutex_t _lockCommands; //protect the command list
	pthread_cond_t _workCond;   //workReady condition
	pthread_mutex_t _workMutex; //protect the workReady signal
	bool _workReady;
	multimap<uint32_t, Command*> _commands;
	
	//processor Data
	uint8_t _id;
	uint32_t _freeIdCount;
	pthread_mutex_t _lockFreeID;
	map<uint32_t, Processable*> _localObjects;
	
	map<uint32_t, SMetaObj*> _metaObjs;
	
	map<Processor*, list<uint32_t> > _initsFrec;
	map<Processor*, list<uint32_t> > _lowFrec;
	map<Processor*, list<uint32_t> > _medFrec;
	map<Processor*, list<uint32_t> > _highFrec;
	map<string,SOrdreProgram*> _programs;
};

#endif	/* PROCESSOR_H */

