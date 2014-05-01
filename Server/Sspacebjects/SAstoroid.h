/* 
 * File:   SAstoroid.h
 * Author: karsten
 *
 * Created on 5. oktober 2011, 20:39
 */

#ifndef SASTOROID_H
#define	SASTOROID_H
#include "SObj.h"
#include "SSubAble.h"
#include "SAstoroidType.h"
#include "../Commands/Processor.h"
class SAstoroidBelt;
class SAstoroid : public SObj, public STargetable , public Processable {
public:
	SAstoroid(uint32_t id, SPos& pos, SAstoroidType& atype, SAstoroidBelt* belt);
	virtual uint32_t getId(){return _id;}
	virtual STargetable* getTargetable(){return (STargetable*)this;}
	virtual void Hit(SShot* shot,uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y);
	virtual uint32_t getTargetSize(){return _size+100;}
	virtual TargetType::Enum getTargetType(){return TargetType::Astoroid;}
	virtual SAstoroid* isAstoroid(){return this;}
	virtual SObj* isObj(){return this;}
	virtual bool canBeRemoved();
	virtual void proces(uint32_t delta, Processor* processor ){}
	void subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){}
	virtual void announceRemovalOf(SObj* obj);
	SAstoroidType* getAstoroidType(){return this->_type;}
	virtual void sendDepleted(SubscriptionLevel::Enum level);
	virtual void sendFull(SubscriptionLevel::Enum level);
	virtual ~SAstoroid();
private:
	SAstoroidType* _type;
	SAstoroidBelt* _belt;
	uint32_t _quan;
};

#endif	/* SASTOROID_H */

