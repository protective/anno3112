/* 
 * File:   SFighter.h
 * Author: karsten
 *
 * Created on 25. januar 2014, 22:33
 */

#ifndef SFIGHTER_H
#define	SFIGHTER_H

#include "SUnit.h"
#include "SFighterType.h"

class SFighter : public SUnit {
public:
	SFighter(uint32_t id, SPos& pos, SFighterType& fType, uint32_t playerId, uint32_t motherShip, uint32_t motherShipSub);
	virtual SFighter* isFighter(){return this;}
	virtual TargetType::Enum getTargetType(){return this->_fType->getTargetType();}
	SFighterType* getFighterType(){return this->_fType;}
	virtual SUnitType* getUnitType(){return _fType;}
	virtual void proces(uint32_t delta, Processor* processor);
	virtual void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level);

	void setMotherShip(uint32_t ship){_motherShip = ship;}
	void setMotherShipSub(uint32_t sub){_motherShipSub = sub;}
	void setMotherShipTarget(uint32_t target){_motherShipTarget = target;}
	void setFighterSignal(FighterSignal::Enum signal);
	
	
	uint32_t getMotherShip(){return _motherShip;}
	uint32_t getMotherShipSub(){return _motherShipSub;}
	uint32_t getMotherShipTarget(){return _motherShipTarget;}
	FighterSignal::Enum getFighterSignal(){return _curSignal;}
	
	virtual ~SFighter();
protected:
	SFighterType* _fType;
	uint32_t _motherShip;
	uint32_t _motherShipSub;
	uint32_t _motherShipTarget;
	FighterSignal::Enum _curSignal;
	
};

#endif	/* SFIGHTER_H */

