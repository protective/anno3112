/* 
 * File:   CSubTypeFighter.h
 * Author: karsten
 *
 * Created on 24. august 2014, 22:31
 */

#ifndef CSUBTYPEFIGHTER_H
#define	CSUBTYPEFIGHTER_H
#include "CSubType.h"

class CSubTypeFighter  : public CSubType {
public:
	CSubTypeFighter();

	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Fighter;}
	virtual CSubTypeFighter* isFighter(){return this;}
	uint32_t getBayCount(){return this->_bayCount;}
	virtual void setBayCount(uint32_t bayCount){this->_bayCount = bayCount;}

	virtual ~CSubTypeFighter();
private:
	uint32_t _bayCount;
};

#endif	/* CSUBTYPEFIGHTER_H */

