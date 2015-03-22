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
	
	void add(SUnit* unit);
	
	map<uint32_t, SGrid*>& getGrids();
	map<uint32_t, SObj*>& getObjs();
	Processor* getProcessor(){return _processors;}
	virtual ~SWorld();
private:
	map<uint32_t, SGrid*> grids;
	map<uint32_t, SObj*> objInWorld;
	uint32_t _time;
	uint32_t _slowTime;
	Processor* _processors;
};

#endif	/* SWORLD_H */

