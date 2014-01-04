/* 
 * File:   CWorld.h
 * Author: karsten
 *
 * Created on 8. februar 2012, 19:44
 */

#ifndef CWORLD_H
#define	CWORLD_H
#include "../CFunctions.h"
#include "CGrid.h"
class CWorld {
public:
	CWorld();
	
	map<uint32_t, CGrid*>& getGrids(){return this->_grids;}
	virtual ~CWorld();
private:
	map<uint32_t, CGrid*> _grids;
};

#endif	/* CWORLD_H */

