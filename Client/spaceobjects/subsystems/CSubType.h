/* 
 * File:   CSubType.h
 * Author: karsten
 *
 * Created on 1. august 2011, 01:13
 */

#ifndef CSUBTYPE_H
#define	CSUBTYPE_H
#include "../../CFunctions.h"
class CSubTypeFac;
class CSubTypeRef;
class CSubTypeWep;
class CSubTypeBonus;
class CSubTypeBoost;
class CSubType {
public:
	CSubType();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Invalid;}
	virtual CSubTypeWep* isWeapon(){return NULL;}
	virtual CSubTypeFac* isFac(){return NULL;}
	virtual CSubTypeRef* isRef(){return NULL;}
	virtual CSubTypeBonus* isBonus(){return NULL;}
	virtual CSubTypeBoost* isBoost(){return NULL;}

	virtual ~CSubType();
private:

};

#endif	/* CSUBTYPE_H */

