/* 
 * File:   CSubSystemFac.h
 * Author: karsten
 *
 * Created on 16. september 2011, 21:31
 */

#ifndef CSUBSYSTEMFAC_H
#define	CSUBSYSTEMFAC_H

#include "CSubSystem.h"
#include "CSubTypeFac.h"
#include "CSingleFac.h"


struct CsybsystemFacQueue{
	CItemType* _item;
	uint32_t _quantity;
};

class CSubSystemFac : public CSubSystem {
public:
	CSubSystemFac(CObj& owner,CSlotNode& slotnode,uint32_t id, CItemType* item, uint32_t Xitem);
	virtual uint32_t AddItem(uint32_t Xitem);
	virtual uint32_t RemoveItem(uint32_t Xitem);
	virtual void proces(uint32_t DTime);
	bool haveEnoughTobuild(CItemType* item);
	virtual int32_t cooldown(uint16_t index){if(_fac.find(index) != _fac.end())return _fac[index]->getDuration(); return 0;}
	virtual int32_t maxcooldown(uint16_t index){return this->_maxcooldown;}
	virtual void setCooldown(uint16_t index,int32_t value){if(_fac.find(index) != _fac.end()) _fac[index]->setDuration(value);}
	virtual void setMaxCooldown(uint16_t index,int32_t value){this->_maxcooldown = value;}
	virtual CSubSystemFac* isFac(){return this;}
	virtual ~CSubSystemFac();
private:
	map<uint32_t,CSingleFac*> _fac;
	CItemType* _curentBuild;
};

#endif	/* CSUBSYSTEMFAC_H */

