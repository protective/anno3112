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
	SWorld();
	void addGrid(SGrid* grid);
	void proces(uint32_t thead_id);

	map<uint32_t, SGrid*>& getGrids();
	map<uint32_t, SObj*>& getObjs();

	virtual ~SWorld();
private:
	map<uint32_t, SGrid*> grids;
	map<uint32_t, SObj*> objInWorld;
};

#endif	/* SWORLD_H */

