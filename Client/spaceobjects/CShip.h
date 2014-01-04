/* 
 * File:   GShip.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:34
 */

#ifndef CSHIP_H
#define	CSHIP_H

#include "CTargetable.h"
#include "CMovable.h"
#include "CObj.h"
#include "subsystems/CSlotNode.h"
#include "../UI/CUIBaseFrame.h"
#include "CSubAble.h"
#include "CShipType.h"
#include "COrdres.h"
class CShip : public CObj , public CMovable , public CTargetable , public CSubAble, public CUIBaseFrame {
public:
	CShip(uint32_t id, uint32_t playerId, CPos& pos, CShipType& stype);
	virtual uint32_t getSize(){return this->_shiptype->getSize();}
	virtual void Draw();
	virtual void predraw(uint32_t level);
	
	virtual void Move(uint32_t deltaT);
	virtual void Proces(uint32_t DTime);
	virtual void Click(SDL_Event event, int32_t x, int32_t y);
	uint32_t AddSub(CItemType* type, uint32_t slot, uint32_t Xitem);
	uint32_t RemoveSub(uint32_t slot, uint32_t Xitem);
	virtual void ResivePosUpdate(CPos& pos);
	virtual CShip* isShip(){return this;}
	virtual CSubAble* issubable(){return (CSubAble*)this;};
	virtual CMovable* isMovable(){return this;}
	virtual CTargetable* isTargetable(){return (CTargetable*)this;}

	void setShield(int32_t amount, uint16_t index){_shield[index] = amount;}
	void setDeflector(int32_t amount){_deflector = amount;}
	void setArmor(int32_t amount){_armor = amount;}
	void setHull(int32_t amount){_hull = amount;}
	CShipType* getShipType(){return this->_shiptype;}

	COrdres* getOrdres(){return this->_order;}
	void setOrdres(COrdres* ordres){this->_order = ordres;}
	void setToBeRemoved(bool b){this->_toBeRemoved = b;}
	bool getToBeRemoved(){return this->_toBeRemoved;}
	virtual int32_t getX(){return 0;}
	virtual int32_t getY(){return 0;}
	virtual int32_t getWight(){return 30000;}
	virtual int32_t getHight(){return 30000;}
	virtual bool canBeRemoved();
	virtual bool isDead();
	virtual ~CShip();
private:
	uint32_t _targetUpdateCounter;
	bool _toBeRemoved;
	CShipType* _shiptype;
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
	COrdres* _order;
	uint32_t _graficCounterPrio;
};

typedef map<uint32_t,CShip*>::iterator CShipI;

#endif	/* CSHIP_H */

