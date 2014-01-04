/* 
 * File:   GObj.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:23
 */

#ifndef COBJ_H
#define	COBJ_H
#include "../CFunctions.h"
#include "CPos.h"

#include "CMovable.h"

class CShot;
class CShip;
class CAstoroid;
class CSubAble;
class CTargetable;
class CObj {
public:
	CObj(uint32_t id, uint32_t playerId, CPos& pos);
	virtual CPos& getPos();
	virtual CPos& getActualPos(){return _actualPos;}
	void MovePos(int32_t x, int32_t y);
	virtual void ResivePosUpdate(CPos& pos);
	uint32_t getId(){return this->_id;}
	virtual void Proces(uint32_t DTime);
	virtual uint32_t getSize(){return 0;}
	virtual CShip* isShip(){return NULL;}
	virtual CAstoroid* isAstoroid(){return NULL;}
	virtual CShot* isShot(){return NULL;}
	virtual CMovable* isMovable(){return NULL;}
	virtual CSubAble* issubable(){return NULL;}
	virtual CTargetable* isTargetable(){return NULL;}
	virtual void announceRemovalOf(CObj* obj){};
	virtual bool canBeRemoved(){return false;}
	virtual bool isDead(){return false;}
	void fadeout(uint16_t time){_fadetimer = 0-time;_maxfadetimer = 0-time;}
	void fadein(uint16_t time){_fadetimer = time;_maxfadetimer = time;}
	virtual uint8_t getTeam(){return _team;}
	virtual uint32_t getPlayerId(){return _playerId;}

	virtual ~CObj();
protected:
	uint32_t _id;
	uint32_t _playerId;
	int32_t _team;
	uint32_t _lastUpdate;
	uint32_t _procedTime;
	CPos _pos;
	CPos _actualPos;
	int16_t _fadetimer;
	int16_t _maxfadetimer;
	list<GCommands*> _playerCommands;
};

typedef map<uint32_t,CObj*>::iterator CobjI;

#endif	/* COBJ_H */

