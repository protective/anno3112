/* 
 * File:   SCargoBay.h
 * Author: karsten
 *
 * Created on 20. september 2011, 13:12
 */

#ifndef SCARGOBAY_H
#define	SCARGOBAY_H
#include "../../SFunctions.h"
class SSubAble;
class SCargoBay {
	typedef map<SItemType*,uint32_t>::iterator SCargoI;

public:
	SCargoBay(SSubAble* owner, uint32_t maxCargo);
	uint32_t getmaxCargo(){return this->_maxCargo;}
	uint32_t getcurCargo(){return this->_curCargo;}
	uint32_t TransfereCargo(SCargoBay* bay,SItemType* item, uint32_t quan);
	uint32_t TransfereCargo(SCargoBay* bay,SItemType* item);
	uint32_t GetReturn(SItemType* item, uint32_t quan);
	uint32_t GetById(uint32_t id);
	uint32_t GetAddReturn(SItemType* item, uint32_t quan);
	uint32_t RemoveReturn(SItemType* item, uint32_t quan);
	uint32_t AddReturn(SItemType* item, uint32_t quan);
	SSubAble* getOwner(){return _owner;}
	map<SItemType*,uint32_t>& getContent(){return this-> _content;}
	virtual void sendCargoUpdate(SubscriptionLevel::Enum level, SItemType* item,uint32_t quan);
	virtual void sendCargoBay(list<uint32_t>& clients);
	virtual ~SCargoBay();
private:
	SSubAble* _owner;
	map<SItemType*,uint32_t> _content;
	uint32_t _maxCargo;
	uint32_t _curCargo;
};

#endif	/* SCARGOBAY_H */

