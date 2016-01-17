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
#include "../Commands/Processor.h"
#include "../Commands/CommandInitShot.h"
#include "subsystems/SSingleWep.h"
#include "subsystems/SSubTypeWep.h"
#include "SSubAble.h"
class SShot : public SObj , public SMovable, public STargetable, public Processable{
public:
	//SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, uint32_t texId, int32_t speed, uint32_t mindmg, uint32_t maxdmg);
	//SShot(uint32_t id, SPos& pos, SSubAble* owner, STargetable* target, uint32_t texId, int32_t speed, uint32_t mindmg, uint32_t maxdmg, DmgTypes::Enum);
	friend CommandInitShot;
	SShot(uint32_t id, SPos& pos, SSubAble* owner, uint32_t target, SSubTypeWep* type, Processor* creator);
	virtual uint32_t getId(){return _id;}
	virtual SPos& getPos(){return _pos;}
	virtual void proces(uint32_t delta, Processor* processor);
	virtual void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level);
	void Move(uint32_t deltaT);
	void MovePos(int32_t x, int32_t y, int32_t z);
	void checkCollisions(list<OBJID> objs);
	void applyDamage(uint32_t target, Shields::Enum shield, int32_t x, int32_t y);
	virtual uint32_t hit(uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y);
	void useDamage(uint32_t damage);
	virtual SShot* isShot(){return this;}
	virtual SObj* isObj(){return this;}
	virtual SGrid* getGrid(){return _pos.grid;}
	virtual bool canBeRemoved();
	virtual SMovable* isMovable(){return this;}
	virtual STargetable* isTargetable(){return this;}
	virtual void setTargetPos(SPos& pos);
	virtual uint32_t getTargetSize(){return _size;}
	virtual TargetType::Enum getTargetType(){return _hp > 0 ? TargetType::Missel: TargetType::Invalid;}
	virtual uint8_t getTeam(){return _team;}
	//virtual SSubAble* getOwner(){return this->_owner;}
	virtual uint32_t getTexId(){return this->_texId;}
	virtual uint32_t getFlightTime(){return this->_flightTime;}
	virtual uint32_t getHp(){return _hp;}
	virtual uint32_t getMaxFlightTime(){return this->_maxFlightTime;}
	virtual DmgTypes::Enum getDmgTypes(){return this->_dmgType;}
	virtual uint32_t getTracking(){return this->_tracking;}
	virtual uint32_t getTrackingTime(){return this->_trackingTime;}
	virtual uint32_t getTarget(){return this->_target;}
	virtual int32_t getMoveX(){return VektorUnitX(this->_pos.d/100) * _speed;}
	virtual int32_t getMoveY(){return -VektorUnitY(this->_pos.d/100) * _speed;}
	virtual int32_t getMoveZ(){return VektorUnitY(this->_moveZ) * _speed;}
	
	
	virtual void sendFull(SubscriptionLevel::Enum level);
	virtual uint32_t getProcId(){return _id;}
	virtual SSubTypeWep* getType(){return _type;}
	virtual ~SShot();
private:
	bool _hasHit;
	OBJID _owner;
	uint32_t _flightTime;
	uint32_t _maxFlightTime;
	uint32_t _tracking;
	uint32_t _trackingTime;
	uint32_t _resolution;
	double _moveZ;
	uint32_t _target;
	uint32_t _texId;
	uint32_t _dmgMin;
	uint32_t _dmgMax;
	uint32_t _hp;
	list<OBJID> _hitlist;
	DmgTypes::Enum _dmgType;
	SSubTypeWep* _type;
	
};

#endif	/* SSHOT_H */

