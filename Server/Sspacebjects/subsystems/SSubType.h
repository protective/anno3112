/* 
 * File:   SSubType.h
 * Author: karsten
 *
 * Created on 30. juni 2011, 16:03
 */

#ifndef SSUBTYPE_H
#define	SSUBTYPE_H
#include "../../SFunctions.h"

class SSubTypeFac;
class SSubTypeWep;
class SSubTypeBoost;
class SSubTypeBonus;
class SSubTypeRef;
class SSubType {
public:
	SSubType();
	virtual SubSystemClass::Enum getClass(){return SubSystemClass::Invalid;}
	//void setName(string value){this->_name = value;}
	//string getName(){return this->_name;}
	virtual SSubTypeWep* isWeapon(){return NULL;}
	virtual SSubTypeFac* isFac(){return NULL;}
	virtual SSubTypeBonus* isBonus(){return NULL;}
	virtual SSubTypeBoost* isBoost(){return NULL;}
	virtual SSubTypeRef* isRef(){return NULL;}
	void setMount(uint32_t value){_mount = value;}
	uint32_t getMount(){return _mount;}
	void setMountType(FitTypes::Enum value){_mountType = value;}
	FitTypes::Enum getMountType(){return _mountType;}
	map<SubKeyWord::Enum,bool>& getSubKeys(){return _subKeys;}
	virtual ~SSubType();
protected:
	uint32_t _mount;
	FitTypes::Enum _mountType;
	map<SubKeyWord::Enum,bool> _subKeys;
};

#endif	/* SSUBTYPE_H */

