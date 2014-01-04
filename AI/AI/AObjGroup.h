/* 
 * File:   AObjGroup.h
 * Author: karsten
 *
 * Created on 6. juni 2012, 23:11
 */

#ifndef AOBJGROUP_H
#define	AOBJGROUP_H
#include "../AFunctions.h"
#include "../Client/spaceobjects/CObj.h"
class ABeacon;
class AObjGroup {
public:
	AObjGroup();
	void setBeacon(ABeacon* beacon){_beacon = beacon;}
	ABeacon* getBeacon(){return _beacon;}
	void addUnit(CObj* obj);
	void removeUnit(CObj* obj);
	void recompute();
	map<uint32_t, CObj*>& getobjs(){return _objs;}
	int32_t getPower(){return _power;}
	int32_t getTactical(){return _tactical;}
	int32_t getThread(){return _thread;}
	uint32_t getHostileCount(){return _hostileCount;}
	uint32_t getFriendlyCount(){return _frindlyCount;}
	CPos& getPos(){return _pos;}
	AObjGroup* splitGroup();
	void subSplitGroup(AObjGroup* g1, AObjGroup* g2);
	virtual ~AObjGroup();
private:
	ABeacon* _beacon;
	map<uint32_t, CObj*> _objs;
	int32_t _power;
	uint32_t _hostileCount;
	uint32_t _frindlyCount;
	int32_t _tactical;
	int32_t _thread;
	CPos _pos;
};

#endif	/* AOBJGROUP_H */

