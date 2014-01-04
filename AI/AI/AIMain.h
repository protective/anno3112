/* 
 * File:   AIMain.h
 * Author: karsten
 *
 * Created on 5. juni 2012, 23:31
 */

#ifndef AIMAIN_H
#define	AIMAIN_H

#include "AObjGroup.h"
#include "ABeacon.h"
#include "UnitControle/AUnitControle.h"


class AIMain {
public:
	AIMain();
	void recreateGroups();
	void findsolution();
	int32_t CalculateUtility();
	virtual ~AIMain();
private:
	ABeacon* findRandomBeacon(AObjGroup* group);

	ABeacon* findrandomCombatBeacon(AObjGroup* group);
	ABeacon* findrandomAllBeacon(AObjGroup* group);
	ABeacon* findownBeacon(AObjGroup* group);
	map<uint32_t, AObjGroup*> _groups;
	map<uint32_t, ABeacon*> _beacons;
	map<uint32_t, AObjGroup*> _combatGroup;
	map<uint32_t, ABeacon*> _unitBeacon;
	uint32_t _curgroup;
};

#endif	/* AIMAIN_H */

