/* 
 * File:   CSubSystemBonus.cpp
 * Author: karsten
 * 
 * Created on 25. december 2011, 18:46
 */

#include "CSubSystemBonus.h"
#include "../CSubAble.h"
CSubSystemBonus::CSubSystemBonus(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem):
CSubSystem(owner,slotnode,id)
{

	this->_type = item;
	this->_xItems = 0;
	this->AddItem(Xitem);
}


void CSubSystemBonus::procesBonus(CSubAble* obj){
	for(map<BonusTypes::Enum, int32_t>::iterator it = this->getTypeBonus()->getBonuslist().begin(); it != this->getTypeBonus()->getBonuslist().end(); it++){
		obj->getBonusList()[it->first]+= (1000*it->second*_xItems);
	}
}


uint32_t CSubSystemBonus::AddItem(uint32_t Xitem){
	if(_xItems > 4)
		cerr<<"WARNING CSubSystemBoost::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	this->_xItems += Xitem;
	return Xitem;
}

uint32_t CSubSystemBonus::RemoveItem(uint32_t Xitem){
	if(_xItems >= Xitem){
		_xItems = _xItems - Xitem;
		return Xitem;
	}else{
		Xitem = _xItems;
		_xItems = 0;
		return Xitem;
	}
	return Xitem;
}

CSubSystemBonus::~CSubSystemBonus() {
}

