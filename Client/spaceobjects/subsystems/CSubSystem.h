/* 
 * File:   CSubSystem.h
 * Author: karsten
 *
 * Created on 31. juli 2011, 23:37
 */

#ifndef CSUBSYSTEM_H
#define	CSUBSYSTEM_H

#include "../CObj.h"
#include "../CTargetable.h"
#include "../../Items/CItemType.h"
class CSlotNode;
class CSubSystemW;
class CSubSystemFac;
class CSubSystemRef;
class CSubSystemBonus;
class CSubSystemBoost;
class CSubSystem {
public:
	CSubSystem(CObj& owner,CSlotNode& slotnode,uint32_t id);
	virtual uint32_t getId(){return this->_id;}
	virtual void proces(uint32_t DTime){}
	virtual int32_t cooldown(uint16_t index){return this->_cooldown;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}
	virtual bool online(){return this->_online;}
	virtual void setOnline(bool online){this->_online = online;}
	
	virtual bool recharge(){return this->_recharge;}
	virtual void setRecharge(bool recharge){this->_recharge = recharge;}

	virtual void setCooldown(uint16_t index,int32_t value){this->_cooldown = value;}
	virtual void setMaxCooldown(uint16_t index,int32_t value){this->_maxcooldown = value;}
	virtual void sethp(uint16_t index,uint32_t value){this->_hp = value;}

	virtual void setXitem(uint32_t value){}

	virtual CObj& getOwner(){return *this->_owner;}
	virtual uint16_t Xitem(){return this->_xItems;}
	virtual uint32_t AddItem(uint32_t Xitem){}
	virtual uint32_t RemoveItem(uint32_t Xitem){}
	virtual CTargetable* getTarget(){return NULL;}
	virtual void setTarget(CTargetable* target){}
	virtual bool canTarget(){return false;}
	virtual CItemType* getItemType(){return this->_type;}
	virtual uint32_t getMaxAmo(){return 0;}
	virtual uint32_t getAmo(){return 0;}
	virtual bool isLocking(uint16_t index){return false;}
	virtual void setMaxAmo(uint32_t amo){}
	virtual void setAmo(uint32_t amo){}
	virtual TargetGroup::Enum getTargetGroup(){return this->_targetGroup;}
	virtual void setTargetGroup(TargetGroup::Enum tg){this->_targetGroup = tg;}
	virtual CSubSystemW* isWeapon(){return NULL;}
	virtual CSubSystemFac* isFac(){return NULL;}
	virtual CSubSystemRef* isRef(){return NULL;}

	virtual CSubSystemBonus* isBonus(){return NULL;}
	virtual CSubSystemBonus* isBoost(){return NULL;}
	
	virtual uint32_t getGraficCounter(){return _graficCounter;}

	virtual ~CSubSystem();
protected:
	CObj* _owner;
	uint32_t _id;
	CSlotNode* _slotnode;
	CItemType* _type;
	int32_t _cooldown;
	int32_t _maxcooldown;
	int32_t _hp;
	int32_t _maxhp;
	uint32_t _xItems;
	bool _online;
	bool _recharge;
	TargetGroup::Enum _targetGroup;
	uint32_t _graficCounter;
};

#endif	/* CSUBSYSTEM_H */

