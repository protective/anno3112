/* 
 * File:   SSubSystemRef.h
 * Author: karsten
 *
 * Created on 23. marts 2012, 23:22
 */

#ifndef SSUBSYSTEMREF_H
#define	SSUBSYSTEMREF_H
#include "SSubSystem.h"
#include "SSubTypeRef.h"
#include "SSingleRef.h"

class SSubSystemRef : public SSubSystem{
public:
	SSubSystemRef(SObj& owner,SSlotNode& slotnode,uint32_t id, SItemType* item, uint32_t Xitem);
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual int32_t cooldown(uint16_t index){if(_ref.find(index) != _ref.end())return _ref[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return _type->getSubType()->isRef()->getCooldown();}
	virtual list<SItemType*>& getQueue(){return this->_refinequeue;}

	virtual void proces();
	virtual ~SSubSystemRef();
private:
	map<uint32_t,SSingleRef*> _ref;
	list<SItemType*> _refinequeue;
};

#endif	/* SSUBSYSTEMREF_H */

