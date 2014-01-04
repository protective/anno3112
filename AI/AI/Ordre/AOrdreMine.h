/* 
 * File:   AOrdreMine.h
 * Author: karsten
 *
 * Created on 2. juli 2012, 21:05
 */

#ifndef AORDREMINE_H
#define	AORDREMINE_H
#include "AOrdre.h"
#include "../Client/spaceobjects/CSubAble.h"
class AOrdreMine : public AOrdre {
public:
	AOrdreMine(CObj* unit, CSubAble* dropof, CPos* location);
	virtual void Execute();
	virtual ~AOrdreMine();
private:
	CObj* _unit;
	CSubAble* _dropof;
	CPos* _location;
	
};

#endif	/* AORDREMINE_H */

