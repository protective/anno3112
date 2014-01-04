/* 
 * File:   SSubSystemFac.h
 * Author: karsten
 *
 * Created on 15. september 2011, 09:39
 */

#ifndef SSUBSYSTEMFAC_H
#define	SSUBSYSTEMFAC_H

#include "SSubSystem.h"
#include "SSubTypeFac.h"
#include "SSingleFac.h"

struct SSubSystemFacQueue{
	SItemType* _item;
	uint32_t _quantity;
};

class SSubSystemFac : public SSubSystem {
public:
	SSubSystemFac(SObj& owner,SSlotNode& slotnode,uint32_t id, SItemType* item, uint32_t Xitem);
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual int32_t cooldown(uint16_t index){if(_fac.find(index) != _fac.end())return _fac[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}
	virtual uint32_t buildItem(SItemType* item,uint32_t quantity);
	virtual void proces();
	virtual SItemType* getCurBuild(){return this->_curentBuild;}
	virtual list<SSubSystemFacQueue>& getQueue(){return this->_queue;}
	virtual ~SSubSystemFac();
private:
	map<uint32_t,SSingleFac*> _fac;
	SItemType* _curentBuild;
	list<SSubSystemFacQueue> _queue;
};

#endif	/* SSUBSYSTEMFAC_H */

