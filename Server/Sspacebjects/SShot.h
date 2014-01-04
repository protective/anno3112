/* 
 * File:   SShot.h
 * Author: karsten
 *
 * Created on 2. juli 2011, 14:23
 */

#ifndef SSHOT_H
#define	SSHOT_H
#include "../SFunctions.h"
#include "SObj.h"
#include "SMovable.h"
#include "STargetable.h"
#include "subsystems/SSingleWep.h"
#include "subsystems/SSubTypeWep.h"
#include "SSubAble.h"
class SShot : public SObj , public SMovable{
public:
	//SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, uint32_t texId, int32_t speed, uint32_t mindmg, uint32_t maxdmg);
	//SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, uint32_t texId, int32_t speed, uint32_t mindmg, uint32_t maxdmg, DmgTypes::Enum);

	SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, SSubTypeWep* type);

	void Move(uint32_t deltaT);
	void MovePos(int32_t x, int32_t y, int32_t z);
	void TestHit();
	void Hit(STargetable* target, Shields::Enum shield, int32_t x, int32_t y);
	virtual SShot* isShot(){return this;}
	virtual bool canBeRemoved();
	virtual SMovable* isMovable(){return this;}
	virtual void setTargetPos(SPos& pos);
	virtual SSubAble* getOwner(){return this->_owner;}
	virtual uint32_t getTexId(){return this->_texId;}
	virtual uint32_t getFlightTime(){return this->_flightTime;}
	virtual uint32_t getMaxFlightTime(){return this->_maxFlightTime;}
	virtual DmgTypes::Enum getDmgTypes(){return this->_dmgType;}
	virtual uint32_t getTracking(){return this->_tracking;}
	virtual uint32_t getTrackingTime(){return this->_trackingTime;}
	virtual STargetable* getTarget(){return this->_target;}
	virtual void announceRemovalOf(SObj* obj){if(_target && _target->obj() == obj)_target = NULL; if(_owner && _owner->obj() == obj)_owner = NULL;};

	virtual ~SShot();
private:
	bool _hasHit;
	uint32_t _flightTime;
	uint32_t _maxFlightTime;
	uint32_t _tracking;
	uint32_t _trackingTime;
	uint32_t _resolution;
	double _moveZ;
	SSubAble* _owner;
	STargetable* _target;
	uint32_t _texId;
	uint32_t _dmgMin;
	uint32_t _dmgMax;
	DmgTypes::Enum _dmgType;
	
};

#endif	/* SSHOT_H */

