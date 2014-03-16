/* 
 * File:   SWorld.h
 * Author: karsten
 *
 * Created on 22. maj 2011, 16:24
 */

#ifndef SWORLD_H
#define	SWORLD_H
#include "../SFunctions.h"
#include "SGrid.h"
class SWorld {
public:
	SWorld(Processor* processors);
	uint32_t getTime(){return _time;}
	void addGrid(SGrid* grid);
	void proces(uint32_t deltaD);
	
	void add(Processable* process);
	
	map<uint32_t, SGrid*>& getGrids();
	map<uint32_t, SObj*>& getObjs();

	virtual ~SWorld();
private:
	map<uint32_t, SGrid*> grids;
	map<uint32_t, SObj*> objInWorld;
	uint32_t _time;
};

#endif	/* SWORLD_H */

