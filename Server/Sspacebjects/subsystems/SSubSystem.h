/* 
 * File:   SSubSystem.h
 * Author: karsten
 *
 * Created on 25. juni 2011, 00:19
 */

#ifndef SSUBSYSTEM_H
#define	SSUBSYSTEM_H


#include "../../SItems/SItemType.h"
#include "SSingleWep.h"

class SObj;
class STargetable;
class SSubAble;
class SSlotNode;
class SSubSystemW;
class SSubSystemBonus;
class SSubSystemFighter;
class SSubSystem {
public:
	SSubSystem(SObj& owner,SSlotNode& slotnode,uint32_t id);
	virtual void proces(){}
	virtual uint32_t getId(){return this->_id;}
	virtual int32_t cooldown(uint16_t index){return this->_cooldown;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}
	virtual bool online(){return this->_online;}
	virtual bool recharge(){return this->_recharge;}
	virtual TargetGroup::Enum getTargetGroup(){return this->_targetGroup;}
	virtual void setTargetGroup(TargetGroup::Enum tg){this->_targetGroup = tg;}
	virtual void setOnline(bool online){this->_online = online;}
	virtual void setRecharge(bool recharge){this->_recharge = recharge;}
	virtual SObj& getOwner(){return *this->_owner;}
	virtual uint16_t Xitem(){return this->_xItems;}
	virtual uint32_t AddItem(uint32_t Xitem){}
	virtual uint32_t RemoveItem(uint32_t Xitem){}
	virtual uint32_t* getTarget(){return NULL;}
	virtual void setTarget(uint32_t* target){}
	virtual void clearTarget(){}
	virtual void announceRemovalOf(SObj* obj){}
	virtual bool canTarget(){return false;}
	virtual SItemType* getItemType(){return this->_type;}
	virtual uint32_t getMaxAmo(){return 0;}
	virtual uint32_t getAmo(){return 0;}
	virtual void setMaxAmo(uint32_t amo){}
	virtual void setAmo(uint32_t amo){}
	SSlotNode* getSlotNode(){return this->_slotnode;}
	virtual SSubSystemW* isWeapon(){return NULL;}
	virtual SSubSystemBonus* isBonus(){return NULL;}
	virtual SSubSystemBonus* isBoost(){return NULL;}
	virtual SSubSystemFighter* isFighter(){return NULL;}
	void reportCharge(SubscriptionLevel::Enum level);
	virtual void reset(){}
	virtual ~SSubSystem();
protected:
	SObj* _owner;
	uint32_t _id;
	SSlotNode* _slotnode;
	SItemType* _type;
	int32_t _cooldown;
	int32_t _maxcooldown;
	uint32_t _xItems;
	bool _online;
	bool _recharge;
	TargetGroup::Enum _targetGroup;
};

#endif	/* SSUBSYSTEM_H */

