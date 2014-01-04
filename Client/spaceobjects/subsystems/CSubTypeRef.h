/* 
 * File:   CSubTypeRef.h
 * Author: karsten
 *
 * Created on 23. marts 2012, 23:23
 */

#ifndef CSUBTYPEREF_H
#define	CSUBTYPEREF_H
#include "CSubType.h"
class CSubTypeRef : public CSubType  {
public:
	CSubTypeRef();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Ref;}
	virtual CSubTypeRef* isRef(){return this;}
	map<uint32_t,CItemType*>& getCanRefineList(){return this->_canRefineList;}
	virtual ~CSubTypeRef();
private:
	map<uint32_t,CItemType*> _canRefineList;
};

#endif	/* CSUBTYPEREF_H */

