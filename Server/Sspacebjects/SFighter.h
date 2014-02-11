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
	SFighter(uint32_t id, SPos& pos, SFighterType& fType, uint32_t playerId);
	virtual SFighter* isFighter(){return this;}
	virtual TargetType::Enum getTargetType(){return this->_fType->getTargetType();}
	SFighterType* getFighterType(){return this->_fType;}

	virtual ~SFighter();
protected:
	SFighterType* _fType;
};

#endif	/* SFIGHTER_H */

