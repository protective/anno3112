/* 
 * File:   SSubSystemFighter.h
 * Author: karsten
 *
 * Created on 4. februar 2014, 19:57
 */

#ifndef SSUBSYSTEMFIGHTER_H
#define	SSUBSYSTEMFIGHTER_H
#include "SSubSystem.h"
class SSubTypeFighter;
class SSubSystemFighter : public SSubSystem  {
public:
	SSubSystemFighter(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem);
	SSubTypeFighter* getTypeFighter(){return (SSubTypeFighter*)this->_type->getSubType();}
	virtual SSubSystemFighter* isFighter(){return this;}
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces();
	virtual int32_t cooldown(uint16_t index){return 0;}
	virtual int32_t maxcooldown(uint16_t index){return 0;}

	virtual ~SSubSystemFighter();
private:
	list<SFighter*> _fighters;
};


#endif	/* SSUBSYSTEMFIGHTER_H */

