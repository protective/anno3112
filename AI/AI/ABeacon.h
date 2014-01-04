/* 
 * File:   ABeacon.h
 * Author: karsten
 *
 * Created on 6. juni 2012, 23:02
 */

#ifndef ABEACON_H
#define	ABEACON_H
#include "../AFunctions.h"
#include "AObjGroup.h"
class ABeacon {
public:
	ABeacon(AObjGroup* group);
	AObjGroup* getGroup(){return _group;}
	int32_t getTotalPower(){return _powerValue + _sumpowerValue;}
	int32_t getTotalThread(){return _threatValue + _sumthreatValue;}
	int32_t getTotalTactical(){return _tacticalValue + _sumtacticalValue;}
	int32_t getTotalEconomic(){return _economicValue + _sumeconomicValue;}
	void add(int32_t power, int32_t thread, int32_t tactical, int32_t economicValue){
		_powerValue += power; _tacticalValue += tactical; _threatValue += thread; _economicValue += economicValue;}
	void addsum(int32_t power, int32_t thread, int32_t tactical, int32_t economicValue){
		_sumpowerValue += power; _sumtacticalValue += tactical; _sumthreatValue += thread; _sumeconomicValue += economicValue;}
	void removesum(int32_t power, int32_t thread, int32_t tactical, int32_t economicValue){
		_sumpowerValue -= power; _sumtacticalValue -= tactical; _sumthreatValue -= thread; _sumeconomicValue -= economicValue;}
	void resetsum(){_sumpowerValue = 0; _sumtacticalValue = 0; _sumthreatValue = 0; _sumeconomicValue = 0;}
	void proces();
	map<uint32_t,float>& getResourses(){return _resourses;}
	void update();
	virtual ~ABeacon();
private:
	AObjGroup* _group;
	map<uint32_t,float> _resourses;
	int32_t _timetolive;
	int32_t _threatValue;
	int32_t _powerValue;
	int32_t _tacticalValue;
	int32_t _economicValue;
	
	int32_t _sumthreatValue;
	int32_t _sumpowerValue;
	int32_t _sumtacticalValue;
	int32_t _sumeconomicValue;
};

#endif	/* ABEACON_H */

