/* 
 * File:   SAstoroidBelt.h
 * Author: karsten
 *
 * Created on 12. april 2012, 20:49
 */

#ifndef SASTOROIDBELT_H
#define	SASTOROIDBELT_H

#include "SObj.h"
#include "SAstoroid.h"
struct SAstoroidBeltRoid{
	SAstoroidBeltRoid(SAstoroidType* type, uint32_t counter){
		_type = type;
		_roid = NULL;
		_counter = 0;
		_maxcounter = counter;
	}
	SAstoroidType* _type;
	SAstoroid* _roid;
	uint32_t _counter;
	uint32_t _maxcounter;
};

class SAstoroidBelt : public  SObj{
public:
	SAstoroidBelt(uint32_t id, SPos& pos);
	virtual void proces();
	void AddRoid(SAstoroidType* type, uint32_t counter);
	virtual void announceRemovalOf(SObj* obj);
	void setSize(uint32_t size){this->_size = size;}
	virtual ~SAstoroidBelt();
private:
	list<SAstoroidBeltRoid*> _roids;
};

#endif	/* SASTOROIDBELT_H */

