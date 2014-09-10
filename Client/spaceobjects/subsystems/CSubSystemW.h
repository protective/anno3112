/* 
 * File:   CSubSystemW.h
 * Author: karsten
 *
 * Created on 31. juli 2011, 23:45
 */

#ifndef CSUBSYSTEMW_H
#define	CSUBSYSTEMW_H

#include "CSubSystem.h"
#include "CSubTypeWep.h"
#include "CSingleWep.h"

class CSubSystemW : public CSubSystem {
public:
	CSubSystemW(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem);
	CSubTypeWep* getTypeWep(){return (CSubTypeWep*)this->_type->getSubType();};
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces(uint32_t DTime);
	virtual CTargetable* getTarget(){return _target;}
	virtual void setTarget(CTargetable* target){this->_target = target;}
	virtual bool canTarget(){return true;}
	
	virtual int32_t cooldown(uint16_t index){if(_weps.find(index) != _weps.end())return _weps[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}

	virtual void setCooldown(uint16_t index,int32_t value){if(_weps.find(index) != _weps.end()) _weps[index]->setDuration(value);}
	virtual void setMaxCooldown(uint16_t index,int32_t value){this->_maxcooldown = value;}

	virtual uint32_t getAmo(){return this->_amo;}
	virtual uint32_t getMaxAmo(){return this->getTypeWep()->getMaxAmo()*_xItems;}
	virtual bool isLocking(uint16_t index);
	virtual void setAmo(uint32_t amo){this->_amo = amo;}
	void setHaveTarget(bool haveTarget){_haveTarget = haveTarget;}
	bool getHaveTarget(){return _haveTarget;}
	uint32_t useAmo(uint32_t amo);
	uint32_t addAmo(uint32_t amo);
	virtual CSubSystemW* isWeapon(){return this;}
	
	virtual ~CSubSystemW();
private:
	map<uint32_t,CSingleWep*> _weps;
	uint32_t _amo;
	
	CTargetable* _target;
	CTargetable* _seqTarget; //target dont change when fireing
	bool _haveTarget;
};

#endif	/* CSUBSYSTEMW_H */

