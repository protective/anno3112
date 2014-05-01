/* 
 * File:   GShip.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:34
 */

#ifndef SSHIP_H
#define	SSHIP_H

#include "SUnit.h"
#include "SShipType.h"

class Client;
class SShip : public SUnit {
public:
	SShip(uint32_t id, SPos& pos, SShipType& stype, uint32_t playerId);
	virtual SShip* isShip(){return this;}
	SShipType* getShipType(){return (SShipType*)this->_sType;}
	virtual SUnitType* getUnitType(){return _sType;}
	virtual void proces(uint32_t delta, Processor* processor);
	virtual ~SShip();
private:
	SShipType* _sType;
};

#endif	/* SSHIP_H */

