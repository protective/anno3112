/* 
 * File:   CPartical.h
 * Author: karsten
 *
 * Created on 9. juli 2011, 15:40
 */

#ifndef CPARTICAL_H
#define	CPARTICAL_H

#include "Grafic.h"
#include "../spaceobjects/CPos.h"
#include "../CFunctions.h"
class CPartical {
public:
	CPartical(ParticalTex::Enum tex, CPos& pos);
	void Proces(uint32_t DTime);
	void Move(uint32_t deltaT);
	bool canBeRemoved(){return this->_tick >=_tickmax;}
	void Draw();
	virtual ~CPartical();
private:
	void MovePos(int32_t x, int32_t y);

	CPos _pos;
	uint32_t _procedTime;
	int32_t _move_x;
	int32_t _move_y;
	int32_t _rotate;
	uint32_t _tick;
	uint32_t _tickmin;
	uint32_t _tickmax;
	ParticalTex::Enum _tex;
};

#endif	/* CPARTICAL_H */

