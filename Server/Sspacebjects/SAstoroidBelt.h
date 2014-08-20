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
#include "../Commands/Processor.h"
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

class SAstoroidBelt : public  SObj , public Processable{
public:
	SAstoroidBelt(uint32_t id, SPos& pos);
	virtual uint32_t getId(){return _id;}
	virtual SObj* isObj(){return this;}
	virtual void proces(uint32_t delta, Processor* processor );
	virtual SGrid* getGrid(){return _pos.grid;}
	void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level);
	void AddRoid(SAstoroidType* type, uint32_t counter);
	void setSize(uint32_t size){this->_size = size;}
	virtual ~SAstoroidBelt();
private:
	list<SAstoroidBeltRoid*> _roids;
};

#endif	/* SASTOROIDBELT_H */

