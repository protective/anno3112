/* 
 * File:   SSubTypeFighter.h
 * Author: karsten
 *
 * Created on 25. januar 2014, 23:54
 */

#ifndef SSUBTYPEFIGHTER_H
#define	SSUBTYPEFIGHTER_H

#include "SSubType.h"
class SFighterType;
class SSubTypeFighter : public SSubType {
public:
	SSubTypeFighter();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Fighter;}

	virtual SSubTypeFighter* isFighter(){return this;}
	void setBayCount(uint32_t bayCount){this->_bayCount = bayCount;}
	uint32_t getBayCount(){return _bayCount;}
	SFighterType* getFighterType(){return this->_fighterType;}
	void setFighterType(SFighterType* type){_fighterType = type;} 
	uint32_t getamoCost(){return 1;}
	uint32_t getMaxCd(){return 100;}
	uint32_t getenegyCost(){return 0;}
	virtual ~SSubTypeFighter();
private:
	uint32_t _bayCount;
	SFighterType* _fighterType;
};

#endif	/* SSUBTYPEFIGHTER_H */

