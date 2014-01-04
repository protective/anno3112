/* 
 * File:   CSubAble.h
 * Author: karsten
 *
 * Created on 1. august 2011, 00:00
 */

#ifndef CSUBABLE_H
#define	CSUBABLE_H

#include "../CFunctions.h"
#include "CObj.h"
#include "subsystems/CSlotNode.h"
#include "cargo/CCargoBay.h"
class CSubAble {
public:
	CSubAble(CObj* obj,uint32_t energy,  uint32_t scanRange, uint32_t scanPRange, uint32_t cargo);
	CObj* obj(){return this->_obj;}
	virtual	uint32_t AddSub(CItemType* type, uint32_t slot, uint32_t Xitem){}
	virtual	uint32_t RemoveSub(uint32_t slot, uint32_t Xitem){}
	virtual ~CSubAble();
	map<uint32_t, CSlotNode*>& getSlots(){return this->slots;}
	CCargoBay* getCargoBay(){return this->_cargoBay;}
	map<BonusTypes::Enum, int32_t>& getBonusList(){return this->_bonuslist;}
	void setEnergy(uint32_t energy){this->_energy = energy;}
	uint32_t getEnergy(){return this->_energy;}
	uint32_t getMaxEnergy(){return this->_maxEnergy;}
	uint32_t getScanRange(){return this->_scanRange;}
	uint32_t getScanPRange(){return this->_scanPRange;}

protected:
	map<uint32_t, CSlotNode*> slots;
	map<BonusTypes::Enum, int32_t> _bonuslist;
	CCargoBay* _cargoBay;
	uint32_t _energy;
	uint32_t _maxEnergy;
		uint32_t _scanRange;
	uint32_t _scanPRange;

private:
	CObj* _obj;

};

typedef map<uint32_t, CSlotNode*>::iterator CslotI;


#endif	/* CSUBABLE_H */

