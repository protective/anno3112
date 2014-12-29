/* 
 * File:   SUnit.h
 * Author: karsten
 *
 * Created on 11. februar 2014, 19:25
 */

#ifndef SUNIT_H
#define	SUNIT_H

#include "../Commands/Processor.h"
#include "STargetable.h"
#include "SMovable.h"
#include "SObj.h"
#include "SProgrammable.h"
#include "SSubAble.h"
#include "SUnitType.h"
#include "SOrdres.h"


#include "subsystems/SSubSystemW.h"
#include "subsystems/SSubSystemBoost.h"
#include "subsystems/SSubSystemFac.h"
#include "subsystems/SSubSystemBonus.h"
#include "subsystems/SSubSystemRef.h"
#include "subsystems/SSubSystemFighter.h"
#include "subsystems/SSlotNode.h"


class SUnit : public SObj , public SMovable , public STargetable, public SSubAble , public Processable, public SProgrammable{
public:
	SUnit(uint32_t id, SPos& pos, SUnitType& stype, uint32_t playerId);
	virtual uint32_t getId(){return _id;}
	virtual SPos& getPos(){return _pos;}
	uint32_t FitAddSub(SItemType* type, uint32_t slot, uint32_t Xitem, SCargoBay* cargobay);
	uint32_t AddSub(SItemType* type, uint32_t slot, uint32_t Xitem);
	uint32_t FitRemoveSub(uint32_t slot, uint32_t Xitem, SCargoBay* cargobay);
	uint32_t RemoveSub(uint32_t slot, uint32_t Xitem);
	void Move(uint32_t deltaT);
	void MovePos(int32_t x, int32_t y);
	void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level);
	virtual void postProces(uint32_t delta);
	virtual void proces(uint32_t delta, Processor* processor);

	virtual void setTargetPos(SPos& pos);
	virtual void setTargetPos(int32_t x, int32_t y);
	virtual void setTargetPos(int32_t x, int32_t y, int32_t d);
	virtual SUnitType* getUnitType(){return NULL;}
	virtual uint32_t getTargetSize(){return _size;}
	virtual uint8_t getTeam(){return _team;}
	virtual SMovable* isMovable(){return this;}
	virtual SObj* isObj(){return this;}
	virtual SSubAble* getsubable(){return (SSubAble*)this;};
	virtual STargetable* isTargetable(){return (STargetable*)this;}
	virtual SUnit* isUnit(){return this;}
	virtual SShip* isShip(){return NULL;}
	virtual SGrid* getGrid(){return _pos.grid;}
	virtual SProgrammable* isProgrammable(){return this;}
	virtual bool canBeRemoved();
	SOrdres* getOrdres(){return this->_order;}
	void setOrdres(SOrdres* ordres);
	virtual TargetType::Enum getTargetType(){return TargetType::Invalid;}

	virtual uint32_t hit(uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y);
	int32_t getShield(uint16_t index){return _shield[index];}
	int32_t getDeflector(){return _deflector;}
	int32_t getArmor(){return _armor;}
	int32_t getHull(){return _hull;}

	int32_t getMaxShield(uint16_t index){return _maxshield[index];}
	int32_t getMaxDeflector(){return _maxdeflector;}
	int32_t getMaxArmor(){return _maxarmor;}
	int32_t getMaxHull(){return _maxhull;}


	void AddDeflector(uint32_t value){_deflector+=value;if(_deflector>_maxdeflector)_deflector= _maxdeflector;}
	void AddShield(uint16_t index, uint32_t value){_shield[index]+=value;if(_shield[index]>_maxshield[index])_shield[index]= _maxshield[index];}
	void AddArmor(uint32_t value){_armor+=value;if(_armor>_maxarmor)_armor= _maxarmor;}
	void AddHull(uint32_t value){_hull+=value;if(_hull>_maxhull)_hull= _maxhull;}
	void ResetLastCombat(){_lastCombat = 0;}
	bool IsOutOfCombat(){if(_lastCombat > 1000)return true; return false;}
	
	//networking
	virtual void sendPosUpdate(SubscriptionLevel::Enum level);
	virtual void sendFull(uint32_t client);
	virtual void sendFull(SubscriptionLevel::Enum level);
	virtual void sendRemoved(SubscriptionLevel::Enum level, DestroyMode::Enum mode);
	virtual void sendHpUdate(SubscriptionLevel::Enum level);
	
	virtual ~SUnit();
protected:
	
	
	
	void updateAutoMove();
	uint16_t _autoMovePoint;
	uint16_t _autoMoveCounter;
	
	uint32_t _targetUpdateCounter;
	int32_t _shield[6];
	int32_t _deflector;
	int32_t _armor;
	int32_t _hull;
	int32_t _maxshield[6];
	bool _shieldDown[6];
	int32_t _maxdeflector;
	bool _deflectorDown;
	int32_t _maxarmor;
	int32_t _maxhull;
	SOrdres* _order;
	uint32_t _lastCombat;

	//********************
	
	
	//********************
	
};

#endif	/* SUNIT_H */

