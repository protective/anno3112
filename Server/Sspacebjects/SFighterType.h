/* 
 * File:   SFighterType.h
 * Author: karsten
 *
 * Created on 10. februar 2014, 21:23
 */

#ifndef SFIGHTERTYPE_H
#define	SFIGHTERTYPE_H

#include "SUnitType.h"
class SFighterType : public SUnitType {
public:
	SFighterType(uint32_t id);
	virtual SUnitType* getUnitType(){return this;}
	virtual ~SFighterType();
protected:

};

#endif	/* SFIGHTERTYPE_H */

