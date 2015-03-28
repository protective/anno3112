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

struct LockedTarget{
	LockedTarget(OBJID target, uint8_t prio, uint32_t range, uint32_t pdestroyed, uint32_t playerid){
		_target = target;
		_range = range;
		_playerid = playerid;
		_prio = prio;
		_pdestroyed = pdestroyed;
	}
	bool operator < (const LockedTarget& s2) const
	{
		if(_prio > s2._prio){
			return true;
		}else if (_prio < s2._prio){
			return false;
		}
		if( _pdestroyed < s2._pdestroyed)
			return true;
		else if (_pdestroyed > s2._pdestroyed)
			return false;
		
		if(_range < s2._range)
			return true;
		else if(_range > s2._range)
			return false;
		
		if(_target < s2._target)
			return true;
		else if(_target > s2._target)
			return false;

		return false;
	}
	OBJID _target;
	uint8_t _prio;
	uint32_t _range;
	uint32_t _pdestroyed;
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
	//void donelocktarget(uint32_t* target){this->_lockedTargets.push_back(*target);}
	void updateTargetsPrio(Processor* processor);
	void updateTargetList(Processor* processor);
	void updateSubTarget(SSubSystem* subsys);
	OBJID getNextTarget(Processor* processor, SSlotNode* st);
	map<uint32_t, SSlotNode*>& getSlots(){return this->slots;}
	SSubSystem* getSubsystem(uint32_t id){
		return this->slots.find(id) != this->slots.end()
			? this->slots.find(id)->second->getSS()
			: NULL;
		}
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
	map<LockedTarget, uint32_t> _lockedTargets;
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
	bool sortTargetsFunction(LockedTarget s1, LockedTarget s2);
};
//typedef list<STargetable*>::iterator STarI;


#endif	/* SSUBABLE_H */

