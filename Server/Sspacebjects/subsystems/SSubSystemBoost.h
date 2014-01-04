/* 
 * File:   SSubSystemBoost.h
 * Author: karsten
 *
 * Created on 24. december 2011, 12:05
 */

#ifndef SSUBSYSTEMBOOST_H
#define	SSUBSYSTEMBOOST_H

#include "SSubSystem.h"
#include "SSubTypeBoost.h"
#include "SSubSystemBonus.h"

class SSubSystemBoost : public SSubSystemBonus {
public:
	SSubSystemBoost(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem);
	SSubTypeBoost* getTypeBoost(){return (SSubTypeBoost*)this->_type->getSubType();}
	virtual SSubSystemBonus* isBoost(){return this;}
	virtual void proces();
	virtual uint32_t getAmo(){return this->_amo;}
	virtual uint32_t getMaxAmo(){return this->getTypeBoost()->getMaxAmo()*_xItems;}
	virtual void setAmo(uint32_t amo){this->_amo = amo;}

	virtual int32_t cooldown(uint16_t index){return this->_cooldown;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}

	uint32_t useAmo(uint32_t amo);
	uint32_t addAmo(uint32_t amo);
	virtual ~SSubSystemBoost();
private:
	uint32_t _amo;
	int32_t _charge;
	uint32_t _rechargeCounter;
};

#endif	/* SSUBSYSTEMBOOST_H */

