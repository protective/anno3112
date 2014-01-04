/* 
 * File:   CSubTypeFac.h
 * Author: karsten
 *
 * Created on 16. september 2011, 21:32
 */

#ifndef CSUBTYPEFAC_H
#define	CSUBTYPEFAC_H

#include "CSubType.h"

class CSubTypeFac : public CSubType {
public:
	CSubTypeFac();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Fac;}
	map<uint32_t,CItemType*>& getCanBuildList(){return this->_canBuildList;}
	virtual CSubTypeFac* isFac(){return this;}

	virtual ~CSubTypeFac();
private:
	map<uint32_t,CItemType*> _canBuildList;

};

#endif	/* CSUBTYPEFAC_H */

