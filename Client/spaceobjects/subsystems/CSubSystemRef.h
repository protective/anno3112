/* 
 * File:   CSubSystemRef.h
 * Author: karsten
 *
 * Created on 23. marts 2012, 23:23
 */

#ifndef CSUBSYSTEMREF_H
#define	CSUBSYSTEMREF_H
#include "CSubSystem.h"
#include "CSubTypeRef.h"
#include "CSingleRef.h"

class CSubSystemRef : public CSubSystem {
public:
	CSubSystemRef(CObj& owner,CSlotNode& slotnode,uint32_t id, CItemType* item, uint32_t Xitem);
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces(uint32_t DTime);
	virtual int32_t cooldown(uint16_t index){if(_ref.find(index) != _ref.end())return _ref[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}
	virtual void setCooldown(uint16_t index,int32_t value){if(_ref.find(index) != _ref.end()) _ref[index]->setDuration(value);}
	virtual void setMaxCooldown(uint16_t index,int32_t value){this->_maxcooldown = value;}
	virtual CSubSystemRef* isRef(){return this;}
	virtual ~CSubSystemRef();
private:
	map<uint32_t,CSingleRef*> _ref;
};

#endif	/* CSUBSYSTEMREF_H */

