/* 
 * File:   CSubTypeWep.h
 * Author: karsten
 *
 * Created on 1. august 2011, 01:19
 */

#ifndef CSUBTYPEWEP_H
#define	CSUBTYPEWEP_H
#include "CSubType.h"

class CSubTypeWep : public CSubType {
public:
	CSubTypeWep();
	CSubTypeWep(int32_t dmgMin, int32_t dmgMax);

	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Wep;}
	virtual CSubTypeWep* isWeapon(){return this;}

	virtual ~CSubTypeWep();

	int32_t getDmgMin(){return this->_dmgMin;}
	int32_t getDmgMax(){return this->_dmgMax;}
	int32_t getMaxCd(){return this->_maxCd;}

	uint32_t getMaxAmo(){return this->_maxAmo;}
	uint32_t getamoCost(){return this->_amoCost;}
	uint32_t getenegyCost(){return this->_enegyCost;}

	virtual void setMaxAmo(uint32_t amo){this->_maxAmo = amo;}
	virtual void setAmoCost(uint32_t amo){this->_amoCost = amo;}

private:

	int32_t _dmgMin;
	int32_t _dmgMax;
	int32_t _maxCd;
	uint32_t _maxAmo;
	uint32_t _amoCost;
	uint32_t _enegyCost;
};

#endif	/* CSUBTYPEWEP_H */

