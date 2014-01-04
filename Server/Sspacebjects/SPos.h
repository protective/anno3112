/* 
 * File:   SPos.h
 * Author: karsten
 *
 * Created on 24. maj 2011, 19:12
 */

#ifndef SPOS_H
#define	SPOS_H
#include "../SFunctions.h"
class SGrid;
class SPos {
public:
	SPos();
	SPos(SPos& pos);
	SPos(int32_t x, int32_t y, int32_t d);
	SPos(SGrid* grid,int32_t x, int32_t y, int32_t d);
	void turn(int32_t deg);
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t d;
	SGrid* grid;
	virtual ~SPos();
private:

};

#endif	/* SPOS_H */

