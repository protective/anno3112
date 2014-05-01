/* 
 * File:   SSubAble.h
 * Author: karsten
 *
 * Created on 2. juli 2011, 12:29
 */

#ifndef SSUBABLE_H
#define	SSUBABLE_H
#include "../SFunctions.h"
#include "subsystems/SSlotNode.h"
#include "STargetable.h"
#include "SObj.h"
#include "cargo/SCargoBay.h"

struct TempSort{
	TempSort(STargetable* target, uint32_t range, uint32_t playerid){
		_target = target;
		_range = range;
		_playerid = playerid;
	}
	bool operator < (const TempSort& s2)
	{
		uint8_t s1prio = 0;
		if (this->_target->getprio().find(this->_playerid) != this->_target->getprio().end())
				s1prio = this->_target->getprio()[this->_playerid];
		uint8_t s2prio = 0;
		if (s2._target->getprio().find(this->_playerid) != s2._target->getprio().end())
			s2prio = s2._target->getprio()[this->_playerid];

		if(s1prio > s2prio){
			return true;
		}
		if(s1prio < s2prio){
			return false;
		}
		if(s1prio == s2prio && this->_range < s2._range)
			return true;
		else
			return false;
		return false;
	}
	STargetable* _target;
	uint32_t _range;
	uint32_t _playerid;
};

class SSubAble {
public:
	SSubAble(SObj* obj, uint32_t energy, uint32_t recharge, uint32_t scanRange, uint32_t scanPRange, uint32_t cargo);
	SObj* obj(){return this->_obj;}
	virtual	uint32_t AddSub(SItemType* type, uint32_t slot, uint32_t Xitem){}
	virtual	uint32_t FitAddSub(SItemType* type, uint32_t slot, uint32_t Xitem, SCargoBay* cargobay){}
	virtual uint32_t RemoveSub(uint32_t slot, uint32_t Xitem){}
	virtual	uint32_t FitRemoveSub(uint32_t slot, uint32_t Xitem, SCargoBay* cargobay){}
	int32_t getEnergy(){return this->_energy;}
	int32_t getRecharge(){return this->_recharge;}
	uint32_t getRecoil(){return this->_recoil;}
	uint32_t useRecoil(uint32_t value){_recoil-= value;}
	uint32_t useEnergy(uint32_t energy);
	uint32_t addEnergy(uint32_t energy);
	uint32_t addRecoil(uint32_t recoil);
	uint32_t getMaxRecoil();
	void donelocktarget(uint32_t* target){this->_lockedTargets.push_back(*target);}
	void updateTargetsPrio(Processor* processor);
	void updateTargetList(Processor* processor);
	void updateSubTarget(SSubSystem* subsys);
	map<uint32_t, SSlotNode*>& getSlots(){return this->slots;}
	SCargoBay* getCargoBay(){return this->_cargoBay;}
	uint32_t* getPrimeTarget(){return _havePrime ? &_primeTarget : NULL;}
	void setPrimeTarget(uint32_t target){_primeTarget = target; _havePrime = true;}
	void clearPrimeTarget(){_havePrime = false;}
	map<BonusTypes::Enum, int32_t>& getBonusList(){return this->_bonuslist;}


	uint32_t getScanRange(){return this->_scanRange;}
	uint32_t getScanPRange(){return this->_scanPRange;}

	virtual int32_t getShield(uint16_t index){}
	virtual int32_t getDeflector(){}
	virtual int32_t getArmor(){}
	virtual int32_t getHull(){}

	virtual	int32_t getMaxShield(uint16_t index){}
	virtual int32_t getMaxDeflector(){}
	virtual int32_t getMaxArmor(){}
	virtual int32_t getMaxHull(){}

	virtual void AddShield(uint16_t index, uint32_t value){}
	virtual void AddDeflector(uint32_t value){}
	virtual void AddArmor(uint32_t value){}
	virtual void AddHull(uint32_t value){}

	virtual ~SSubAble();
protected:
	map<uint32_t, SSlotNode*> slots;
	list<uint32_t> _lockedTargets;
	SCargoBay* _cargoBay;
	map<BonusTypes::Enum, int32_t> _bonuslist;
	uint32_t _primeTarget;
	bool _havePrime;
	int32_t _energy;
	int32_t _maxEnergy;
	int32_t _recharge;
	uint32_t _scanRange;
	uint32_t _scanPRange;
	uint32_t _recoil;
	
	
private:
	SObj* _obj;
	bool sortTargetsFunction(TempSort s1, TempSort s2);
};
//typedef list<STargetable*>::iterator STarI;


#endif	/* SSUBABLE_H */

