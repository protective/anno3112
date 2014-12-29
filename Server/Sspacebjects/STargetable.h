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
	virtual SPos& getPos() = 0;
	virtual uint32_t getTargetSize() = 0;
	virtual uint8_t getTeam() = 0;
	virtual uint32_t hit(uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y){cerr<<"hit targetable ??"<<endl;}
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

