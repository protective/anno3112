/* 
 * File:   SCargoBay.h
 * Author: karsten
 *
 * Created on 20. september 2011, 13:12
 */

#ifndef SCARGOBAY_H
#define	SCARGOBAY_H
#include "../../SFunctions.h"

typedef struct transfereOperation{
	transfereOperation(){
		_id = 0;
		_toId = 0;
		_itemId = 0;
		_remaning = 0;
	}
	transfereOperation(uint32_t id, OBJID toId, uint32_t itemId, uint32_t remaning){
		_id = id;
		_toId = toId;
		_itemId = itemId;
		_remaning = remaning;
    }
	transfereOperation(const transfereOperation& v){
		_id = v._id;
		_toId = v._toId;
		_itemId = v._itemId;
		_remaning = v._remaning;
    }
	uint32_t _id;
	OBJID _toId;
	uint32_t _itemId;
	uint32_t _remaning;
}transfereOperation;

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
	uint32_t GetCur(uint32_t id);
	uint32_t GetAddReturn(SItemType* item, uint32_t quan);
	uint32_t RemoveReturn(SItemType* item, uint32_t quan);
	uint32_t AddReturn(SItemType* item, uint32_t quan);
	SSubAble* getOwner(){return _owner;}
	map<SItemType*,uint32_t>& getContent(){return this-> _content;}
	virtual void sendCargoUpdate(SubscriptionLevel::Enum level, SItemType* item,uint32_t quan);
	virtual void sendCargoBay(list<uint32_t>& clients);
	
	void proces(uint32_t deltaT);


	uint32_t useIncommingCredit(uint32_t credit){uint32_t i = _incommingCredit >= credit ? credit : _incommingCredit; _incommingCredit -=i; return i;}		
	uint32_t addIncommingCredit(uint32_t credit){ _incommingCredit +=credit; return credit;}		
	uint32_t addOutgoingCredit(uint32_t credit){ _outgoingCredit +=credit; return credit;}		
	map<uint32_t, transfereOperation>& getTransferes(){return _transferes;}
	void addTransfere(uint32_t toShipId, uint32_t itemType, uint32_t quan);
	virtual ~SCargoBay();
private:
	uint32_t sendItem(uint32_t toShip, uint32_t item, uint32_t quan);

	
	SSubAble* _owner;
	map<SItemType*,uint32_t> _content;
	uint32_t _maxCargo;
	uint32_t _curCargo;
	uint32_t _procesTimer;
	uint32_t _outgoingCredit;
	uint32_t _incommingCredit;
	map<uint32_t, transfereOperation> _transferes;
};

#endif	/* SCARGOBAY_H */

