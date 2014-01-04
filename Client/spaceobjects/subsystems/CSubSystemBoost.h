/* 
 * File:   CSubSystemBoost.h
 * Author: karsten
 *
 * Created on 25. december 2011, 18:46
 */

#ifndef CSUBSYSTEMBOOST_H
#define	CSUBSYSTEMBOOST_H
#include "CSubSystem.h"
#include "CSubType.h"
#include "CSubSystemBonus.h"
#include "CSubTypeBoost.h"

class CSubSystemBoost : public CSubSystemBonus {
public:
	CSubSystemBoost(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem);
	CSubTypeBoost* getTypeBoost(){return (CSubTypeBoost*)this->_type->getSubType();};
	
	virtual void proces(uint32_t DTime);

	virtual uint32_t getAmo(){return this->_amo;}
	virtual uint32_t getMaxAmo(){return this->getTypeBoost()->getMaxAmo()*_xItems;}
	virtual void setAmo(uint32_t amo){this->_amo = amo;}
	
	virtual ~CSubSystemBoost();
private:
	uint32_t _amo;
};

#endif	/* CSUBSYSTEMBOOST_H */

