/* 
 * File:   SSubTypeFac.h
 * Author: karsten
 *
 * Created on 15. september 2011, 12:55
 */

#ifndef SSUBTYPEFAC_H
#define	SSUBTYPEFAC_H

#include "SSubType.h"
class SSubTypeFac : public SSubType{
public:
	SSubTypeFac();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Fac;}
	map<uint32_t,SItemType*>& getCanBuildList(){return this->_canBuildList;}
	virtual SSubTypeFac* isFac(){return this;}
	virtual ~SSubTypeFac();
private:
	map<uint32_t,SItemType*> _canBuildList;
};

#endif	/* SSUBTYPEFAC_H */

