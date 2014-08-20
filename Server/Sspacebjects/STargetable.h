/* 
 * File:   CTargetable.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:32
 */

#ifndef STARGETABLE_H
#define	STARGETABLE_H

#include "SObj.h"

class STargetable {
public:
	STargetable(SObj* obj);
	SObj* obj(){return this->_obj;}
	virtual void hit(uint32_t shot, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y){}
	virtual TargetType::Enum getTargetType(){return TargetType::Invalid;}
	virtual void sendTargetHit(SubscriptionLevel::Enum level, uint32_t shot, ParticalTex::Enum tex, int32_t x, int32_t y);
	virtual map<uint32_t,int8_t>& getprio(){return this->_prio;}
	virtual STargetable* isTargetable(){return this;}
	virtual ~STargetable();
protected:
	map<uint32_t,int8_t> _prio;
private:
	SObj* _obj;
	
};

#endif	/* STARGETABLE_H */

