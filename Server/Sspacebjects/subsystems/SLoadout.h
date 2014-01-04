/* 
 * File:   SLoadout.h
 * Author: karsten
 *
 * Created on 1. marts 2012, 10:15
 */

#ifndef SLOADOUT_H
#define	SLOADOUT_H
#include "../../SFunctions.h"
#include "SSubType.h"
class SShipType;
class SSubAble;
class SCargoBay;

struct singleload{
	SItemType* _type;
	uint32_t _xitem;
	TargetGroup::Enum _targetGroup;
};

class SLoadout {
public:
	SLoadout(uint32_t id, string name, SShipType& shipType);
	map<uint32_t,singleload>& getItems(){return _items;}
	uint32_t getId(){return _id;}
	SShipType* getShipType(){return _shipType;}
	string getName(){return this->_name;}
	void addItem(uint32_t slot, SItemType* type, uint32_t xitem, TargetGroup::Enum targetGroup);
	void fitTo(SSubAble* obj, SCargoBay* fromCargo);
	virtual ~SLoadout();
private:
	uint32_t _id;
	SShipType* _shipType;
	map<uint32_t,singleload> _items;
	string _name;
};

#endif	/* SLOADOUT_H */

