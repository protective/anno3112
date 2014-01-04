/* 
 * File:   CSubSystemBonus.h
 * Author: karsten
 *
 * Created on 25. december 2011, 18:46
 */

#ifndef CSUBSYSTEMBONUS_H
#define	CSUBSYSTEMBONUS_H
#include "CSubSystem.h"
#include "CSubTypeBonus.h"

class CSubSystemBonus : public CSubSystem {
public:
	CSubSystemBonus(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem);
	CSubTypeBonus* getTypeBonus(){return (CSubTypeBonus*)this->_type->getSubType();}
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	void procesBonus(CSubAble* obj);
	virtual CSubSystemBonus* isBonus(){return this;}

	virtual ~CSubSystemBonus();
private:

};

#endif	/* CSUBSYSTEMBONUS_H */

