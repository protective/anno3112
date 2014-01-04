/* 
 * File:   SSubSystemBonus.h
 * Author: karsten
 *
 * Created on 24. december 2011, 12:05
 */

#ifndef SSUBSYSTEMBONUS_H
#define	SSUBSYSTEMBONUS_H
#include "SSubSystem.h"
#include "SSubTypeBonus.h"

class SSubSystemBonus : public SSubSystem {
public:
	SSubSystemBonus(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem);
	SSubTypeBonus* getTypeBonus(){return (SSubTypeBonus*)this->_type->getSubType();}
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual SSubSystemBonus* isBonus(){return this;}
	virtual ~SSubSystemBonus();
	void procesBonus(SSubAble* obj);
private:
	

};

#endif	/* SSUBSYSTEMBONUS_H */

