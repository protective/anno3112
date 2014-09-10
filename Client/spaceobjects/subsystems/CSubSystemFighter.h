/* 
 * File:   CSubSystemFighter.h
 * Author: karsten
 *
 * Created on 24. august 2014, 22:32
 */

#ifndef CSUBSYSTEMFIGHTER_H
#define	CSUBSYSTEMFIGHTER_H
#include "CSubSystem.h"
#include "CSubTypeFighter.h"

class CSubSystemFighter : public CSubSystem  {
public:
	CSubSystemFighter(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem);
	CSubTypeFighter* getTypeFig(){return (CSubTypeFighter*)this->_type->getSubType();};
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces(uint32_t DTime);
	virtual CTargetable* getTarget(){return _target;}
	virtual void setTarget(CTargetable* target){this->_target = target;}
	virtual bool canTarget(){return true;}
	
	virtual int32_t cooldown(uint16_t index){ return 0;}
	virtual int32_t maxcooldown(uint16_t index){return 100;}

	virtual void setCooldown(uint16_t index,int32_t value){}
	virtual void setMaxCooldown(uint16_t index,int32_t value){this->_maxcooldown = value;}

	virtual uint32_t getAmo(){return this->_baycount;}
	virtual uint32_t getMaxAmo(){return this->getTypeFig()->getBayCount() *_xItems;}
	virtual bool isLocking(uint16_t index);
	virtual void setAmo(uint32_t amo){this->_baycount = amo;}
	void setHaveTarget(bool haveTarget){_haveTarget = haveTarget;}
	bool getHaveTarget(){return _haveTarget;}
	uint32_t useAmo(uint32_t amo);
	uint32_t addAmo(uint32_t amo);
	
	virtual ~CSubSystemFighter();
private:
	uint32_t _baycount;
	
	CTargetable* _target;
	CTargetable* _seqTarget; //target dont change when fireing
	bool _haveTarget;
};

#endif	/* CSUBSYSTEMFIGHTER_H */

