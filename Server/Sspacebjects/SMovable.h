/* 
 * File:   CMovable.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:33
 */

#ifndef SMOVABLE_H
#define	SMOVABLE_H


#include "../SFunctions.h"
#include "SPos.h"
#include "SObj.h"
class SMovable {
public:
	SMovable(SObj* obj, int32_t topSpeed, uint32_t agility);
	SObj* obj(){return this->_obj;}
	virtual void Move(uint32_t deltaT){}
	virtual void MovePos(int32_t x, int32_t y){}
	virtual int32_t getMoveX(){return (VektorUnitX(this->_obj->getPos().d/100) * _speed) / 100;}
	virtual int32_t getMoveY(){return -((VektorUnitY(this->_obj->getPos().d/100)* _speed)) / 100;}
	virtual int32_t getMoveZ(){return 0;}
	SPos& getTargetPos();
	int32_t getSpeed(){return this->_speed;}
	int32_t getTopSpeed(){return this->_topSpeed;}
	uint32_t getAgility(){return this->_agility;}
	uint32_t getMovementStatus(){return this->_MovementStatus;}
	virtual void setTargetPos(SPos& pos);
	virtual ~SMovable();
protected:

	SPos _targetPos;
	uint32_t _MovementStatus;
	uint32_t _rangeToTargetPos;
	int32_t _speed;
	int32_t _maxSpeed;
	int32_t _topSpeed;
	uint32_t _agility;
private:
	SObj* _obj;
};

#endif	/* SMOVABLE_H */

