/* 
 * File:   GShip.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:34
 */

#ifndef SSHIP_H
#define	SSHIP_H

#include "STargetable.h"
#include "SMovable.h"
#include "SObj.h"
#include "subsystems/SSlotNode.h"
#include "SSubAble.h"
#include "SShipType.h"
#include "SOrdres.h"

class SShip : public SObj , public SMovable , public STargetable, public SSubAble {
public:
	SShip(uint32_t id, SPos& pos, SShipType& stype, uint32_t playerId);
	uint32_t FitAddSub(SItemType* type, uint32_t slot, uint32_t Xitem, SCargoBay* cargobay);
	uint32_t AddSub(SItemType* type, uint32_t slot, uint32_t Xitem);
	uint32_t FitRemoveSub(uint32_t slot, uint32_t Xitem, SCargoBay* cargobay);
	uint32_t RemoveSub(uint32_t slot, uint32_t Xitem);
	void Move(uint32_t deltaT);
	void MovePos(int32_t x, int32_t y);
	virtual void proces();
	virtual void postProces();
	virtual void setTargetPos(SPos& pos);
	virtual void setTargetPos(int32_t x, int32_t y, int32_t d);
	virtual SShip* isShip(){return this;}
	virtual SMovable* isMovable(){return this;}
	virtual SSubAble* getsubable(){return (SSubAble*)this;};
	virtual STargetable* getTargetable(){return (STargetable*)this;}
	virtual bool canBeRemoved();
	virtual void announceRemovalOf(SObj* obj);
	SOrdres* getOrdres(){return this->_order;}
	void setOrdres(SOrdres* ordres){this->_order = ordres;}
	//targetable
	virtual void Hit(SShot* shot,uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y);
	virtual TargetType::Enum getTargetType(){return this->_sType->getTargetType();}
	int32_t getShield(uint16_t index){return _shield[index];}
	int32_t getDeflector(){return _deflector;}
	int32_t getArmor(){return _armor;}
	int32_t getHull(){return _hull;}

	int32_t getMaxShield(uint16_t index){return _maxshield[index];}
	int32_t getMaxDeflector(){return _maxdeflector;}
	int32_t getMaxArmor(){return _maxarmor;}
	int32_t getMaxHull(){return _maxhull;}

	SShipType* getShipType(){return this->_sType;}

	void AddDeflector(uint32_t value){_deflector+=value;if(_deflector>_maxdeflector)_deflector= _maxdeflector;}
	void AddShield(uint16_t index, uint32_t value){_shield[index]+=value;if(_shield[index]>_maxshield[index])_shield[index]= _maxshield[index];}
	void AddArmor(uint32_t value){_armor+=value;if(_armor>_maxarmor)_armor= _maxarmor;}
	void AddHull(uint32_t value){_hull+=value;if(_hull>_maxhull)_hull= _maxhull;}
	void ResetLastCombat(){_lastCombat = 0;}
	bool IsOutOfCombat(){if(_lastCombat > 1000)return true; return false;}
	virtual ~SShip();
private:

	void updateAutoMove();
	uint16_t _autoMovePoint;
	uint16_t _autoMoveCounter;
	SShipType* _sType;
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
};

#endif	/* SSHIP_H */

