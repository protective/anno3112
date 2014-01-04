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
class SShip;
class SAstoroid;
class SSubAble;
class STargetable;
class SMovable;
class SObj {
public:
	SObj(uint32_t id, SPos& pos, uint8_t team, uint32_t playerId);
	uint32_t getId();
	SPos& getPos();
	SPos& getOldPos();
	uint32_t getSize(){return _size;}
	virtual uint32_t getTargetSize(){return _size;}
	virtual SpaceTypes::Enum getmyType();
	virtual void proces(){};
	virtual void postProces(){};
	virtual void announceRemovalOf(SObj* obj){};
	virtual bool canBeRemoved(){return false;}
	virtual SShip* isShip(){return NULL;}
	virtual SAstoroid* isAstoroid(){return NULL;}
	virtual SShot* isShot(){return NULL;}
	virtual SMovable* isMovable(){return NULL;}
	virtual uint8_t getTeam(){return _team;}
	virtual uint32_t getPlayerId(){return _playerId;}
	virtual SSubAble* getsubable(){return NULL;}
	virtual STargetable* getTargetable(){return NULL;}
	virtual void setUpdateCounter(uint32_t value){this->_updateCounter = value;}
	virtual uint32_t getUpdateCounter(){return this->_updateCounter;}
	virtual map<int8_t,Visibility::Enum>& getVisibleTo(){return this->_visibleTo;}
	virtual map<uint32_t, SPos*>& getOrdrePos(){return this->_ordrePos;}
	virtual map<uint32_t, SObj*>& getOrdreObj(){return this->_ordreObj;}
	virtual bool IsOutOfCombat() {return false;}
	virtual ~SObj();
protected:
	SPos _pos;
	SPos _oldPos;
	uint32_t _id;
	uint32_t _size;
	uint8_t _team;
	map<int8_t,Visibility::Enum> _visibleTo;

	uint32_t _playerId;
	uint32_t _updateCounter;
	pthread_mutex_t lockUnit;
	map<uint32_t, SPos*> _ordrePos;
	map<uint32_t, SObj*> _ordreObj;
};
typedef map<uint32_t,SObj*>::iterator SObjI;
#endif	/* SOBJ_H */

