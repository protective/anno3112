/* 
 * File:   GObj.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:23
 */

#ifndef SOBJ_H
#define	SOBJ_H
#include "../SFunctions.h"
#include "SPos.h"

class SShot;
class SUnit;
class SShip;
class SFighter;
class SAstoroid;
class SSubAble;
class STargetable;
class SMovable;
class Client;
class SObj {
public:
	SObj(uint32_t id, SPos& pos, uint8_t team, uint32_t playerId);
	virtual uint32_t getId() = 0;
	SPos& getPos();
	SPos& getOldPos();
	uint32_t getSize(){return _size;}
	virtual uint32_t getTargetSize(){return _size;}
	virtual SpaceTypes::Enum getmyType();
	//virtual void proces(){};
	virtual void postProces(){};
	virtual void announceRemovalOf(SObj* obj){};
	virtual bool canBeRemoved(){return false;}
	virtual SUnit* isUnit(){return NULL;}
	virtual SShip* isShip(){return NULL;}
	virtual SFighter* isFighter(){return NULL;}
	virtual SAstoroid* isAstoroid(){return NULL;}
	virtual SShot* isShot(){return NULL;}
	virtual SMovable* isMovable(){return NULL;}
	virtual uint8_t getTeam(){return _team;}
	virtual uint32_t getPlayerId(){return _playerId;}
	virtual SSubAble* getsubable(){return NULL;}
	virtual STargetable* getTargetable(){return NULL;}
	virtual void setUpdateCounter(uint32_t value){this->_updateCounter = value;}
	virtual uint32_t getUpdateCounter(){return this->_updateCounter;}
	virtual map<int8_t,Visibility::Enum>& getVisibleTo(){}
	virtual map<uint32_t, SPos*>& getOrdrePos(){return this->_ordrePos;}
	virtual map<uint32_t, SObj*>& getOrdreObj(){return this->_ordreObj;}
	virtual bool IsOutOfCombat() {return false;}
	virtual map<SubscriptionLevel::Enum, list<uint32_t> >& getSubscribers(){return this->_subscriptions;}
	virtual ~SObj();
protected:
	SPos _pos;
	uint32_t _id;
	SPos _oldPos;
	
	uint32_t _size;
	uint8_t _team;

	map<SubscriptionLevel::Enum, list<uint32_t> > _subscriptions;
	uint32_t _playerId;
	uint32_t _updateCounter;
	pthread_mutex_t lockUnit;
	map<uint32_t, SPos*> _ordrePos;
	map<uint32_t, SObj*> _ordreObj;
};
typedef map<uint32_t,SObj*>::iterator SObjI;
#endif	/* SOBJ_H */

