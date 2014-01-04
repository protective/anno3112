/* 
 * File:   SSubTypeRef.h
 * Author: karsten
 *
 * Created on 23. marts 2012, 23:22
 */

#ifndef SSUBTYPEREF_H
#define	SSUBTYPEREF_H
#include "SSubType.h"
class SSubTypeRef : public SSubType{
public:
	SSubTypeRef();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Ref;}
	map<uint32_t,SItemType*>& getCanRefineList(){return this->_canRefineList;}
	virtual uint32_t getCooldown(){return _cooldown;}
	virtual void setCooldown(uint32_t cooldown){this->_cooldown = cooldown;}
	virtual SSubTypeRef* isRef(){return this;}
	virtual ~SSubTypeRef();
private:
map<uint32_t,SItemType*> _canRefineList;
uint32_t _cooldown;
};

#endif	/* SSUBTYPEREF_H */

