/* 
 * File:   AUnitControle.h
 * Author: karsten
 *
 * Created on 29. juni 2012, 16:37
 */

#ifndef AUNITCONTROLE_H
#define	AUNITCONTROLE_H
#include "../../AFunctions.h"
#include "../Client/spaceobjects/CShip.h"
#include "../AChoice.h"

struct AUnitTimeValue{
	AUnitTimeValue(){
	_time = 0;
	_value = 0;
	}
	uint32_t _time;
	uint32_t _value;
};

class AUnitControle {
public:
	AUnitControle();
	void UpdatePosibleChoises(map<uint32_t, ABeacon*>& beacons);
	void SetUnitFocus(float power,uint32_t totalPower, float economic, uint32_t totalEconomic){_power = power; _economic = economic; _totalPower = totalPower; _totalEconomic = totalEconomic;}
	virtual ~AUnitControle();
	map<uint32_t, CShip*>& getChoiceUnits(){return _choiceUnits;}
	AChoice* getRandomChoice(uint32_t unit);
	map<uint32_t, bool>& getShipFit(){return _shipsFits;}
	map<uint32_t,uint32_t>& getShipTypePower(){return _shiptypePower;}
	CShip* getClosestProductionUnit();
private:
	//map<uint32_t,CPos*> _unitMiningLocations;
	//map<CItemType*, AChoice*> _missingItems; //list of items missing and a choise to build them
	map<uint32_t, CShip*> _productionUnits;//list of unit there can produce
	map<uint32_t, CShip*> _choiceUnits;//list of units to be consitered for choice
	map<uint32_t, list<AChoice*> > _choices; //list of choices a unit can make
	map<uint32_t, bool> _shipsFits; //TODO implement client fits for now hardcode
	map<uint32_t, AUnitTimeValue> _miningUnits;
	map<uint32_t, float> _missingMaterials;
	map<uint32_t, int32_t> _missingMaterialsCount;
	map<uint32_t,uint32_t> _shiptypePower;
	float _power, _economic;
	uint32_t _totalPower, _totalEconomic;
	void updateKeyUnits();
	list<ABeacon*> findMiningBeacon(map<uint32_t, ABeacon*>& beacons);
	
};

#endif	/* AUNITCONTROLE_H */

