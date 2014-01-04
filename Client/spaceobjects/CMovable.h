/* 
 * File:   CMovable.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:33
 */

#ifndef CMOVABLE_H
#define	CMOVABLE_H


#include "../CFunctions.h"
#include "CPos.h"
#include "CObj.h"
class CMovable {
public:
	CMovable(CObj* obj, int32_t topSpeed, uint32_t agility);
	CObj* obj(){return this->_obj;}
	virtual void Move(uint32_t deltaT){}
	CPos& getTargetPos();
	int32_t getTopSpeed(){return this->_topSpeed;}
	int32_t getSpeed(){return this->_speed;}
	uint32_t getAgility(){return this->_agility;}
	uint32_t getMovementStatus(){return this->_MovementStatus;}
	void setSpeed(int32_t speed){_speed = speed;}
	void setMovementStatus(uint32_t moveST){_MovementStatus= moveST;}
	virtual ~CMovable();
protected:
	CObj* _obj;
	CPos _targetPos;
	uint32_t _MovementStatus;
	int32_t _ofsetX;
	int32_t _ofsetY;
	int32_t _speed;
	int32_t _maxSpeed;
	int32_t _topSpeed;
	uint32_t _agility;
};

#endif	/* CMOVABLE_H */

