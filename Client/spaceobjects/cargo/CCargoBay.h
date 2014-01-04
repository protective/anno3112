/* 
 * File:   CCargoBay.h
 * Author: karsten
 *
 * Created on 20. september 2011, 19:44
 */

#ifndef CCARGOBAY_H
#define	CCARGOBAY_H
#include "../../CFunctions.h"
class CSubAble;
class CCargoBay {
		typedef map<CItemType*,uint32_t>::iterator CCargoI;

public:
	CCargoBay(CSubAble* owner, uint32_t cargo);
	uint32_t getmaxCargo(){return this->_maxCargo;}
	uint32_t getcurCargo(){return this->_curCargo;}
	uint32_t TransfereCargo(CCargoBay bay,CItemType* item, uint32_t quan);
	uint32_t TransfereCargo(CCargoBay bay,CItemType* item);
	uint32_t GetReturn(CItemType* item, uint32_t quan);
	uint32_t RemoveReturn(CItemType* item, uint32_t quan);
	uint32_t AddReturn(CItemType* item, uint32_t quan);
	CSubAble* getOwner(){return _owner;}
	map<CItemType*,uint32_t>& getContent(){_change = true;return this-> _content;}
	void updateCurCargo();
	bool getChange(){return this->_change;}
	void resetChange(){this->_change = false;}
	void setChange(){this->_change = true;updateCurCargo();}
	virtual ~CCargoBay();
private:
	bool _change;
	CSubAble* _owner;
	map<CItemType*,uint32_t> _content;
	uint32_t _maxCargo;
	uint32_t _curCargo;
};

#endif	/* CCARGOBAY_H */

