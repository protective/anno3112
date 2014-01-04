/* 
 * File:   CLoadout.h
 * Author: karsten
 *
 * Created on 1. marts 2012, 20:04
 */

#ifndef CLOADOUT_H
#define	CLOADOUT_H
#include "../../CFunctions.h"
#include "CSubType.h"
class CShipType;
class CSubAble;
class CCargoBay;

struct singleload{
	CItemType* _type;
	uint32_t _xitem;
	TargetGroup::Enum _targetGroup;
};
class CLoadout {
public:
	CLoadout(uint32_t id, string name, CShipType& shipType);
	map<uint32_t,singleload>& getItems(){return _items;}
	uint32_t getId(){return _id;}
	CShipType* getShipType(){return _shipType;}
	string getName(){return this->_name;}
	virtual ~CLoadout();
private:
	uint32_t _id;
	CShipType* _shipType;
	map<uint32_t,singleload> _items;
	string _name;
};

#endif	/* CLOADOUT_H */

