/* 
 * File:   SSubSystemW.h
 * Author: karsten
 *
 * Created on 25. juni 2011, 01:44
 */

#ifndef SSUBSYSTEMW_H
#define	SSUBSYSTEMW_H

#include "SSubSystem.h"
#include "SSubTypeWep.h"
#include "SSingleWep.h"


class SSubSystemW : public SSubSystem {
public:
	SSubSystemW(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem);
	SSubTypeWep* getTypeWep(){return (SSubTypeWep*)this->_type->getSubType();}
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces();
	virtual int32_t cooldown(uint16_t index){if(_weps.find(index) != _weps.end())return _weps[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}

	
	virtual STargetable* getSeqTarget(){return _seqTarget;}

	virtual void setTarget(uint32_t target){_target = target; _haveTarget = true;}
	virtual void clearTarget(){this->_haveTarget = false;}
	virtual uint32_t* getTarget(){return _haveTarget ? &_target : NULL;}
	
	virtual void setSeqTarget(STargetable* seqTarget){this->_seqTarget = seqTarget;}
	virtual void announceRemovalOf(SObj* obj);
	virtual bool canTarget(){return true;}
	virtual ~SSubSystemW();
	virtual uint32_t getAmo(){return this->_amo;}
	virtual uint32_t getMaxAmo(){return this->getTypeWep()->getMaxAmo()*_xItems;}
	virtual void setAmo(uint32_t amo){this->_amo = amo;}
	uint32_t useAmo(uint32_t amo);
	uint32_t addAmo(uint32_t amo);
	uint32_t getfireseq(){return this->_fireseq;}
	void setfireseq(uint32_t val){this->_fireseq = val;}
	void resetLockPower();
	uint32_t getlockingAgainstPower(){return _lockingAgainstPower;}
	virtual SSubSystemW* isWeapon(){return this;}
	virtual void reset();
private:
	map<uint32_t,SSingleWep*> _weps;
	uint32_t _amo;
	uint32_t _rechargeCounter;
	
	uint32_t _target;
	bool _haveTarget;
	uint32_t _seqTarget; //target dont change when fireing
	uint32_t _fireseq;
	uint32_t _lockingAgainstPower;
};

#endif	/* SSUBSYSTEMW_H */

