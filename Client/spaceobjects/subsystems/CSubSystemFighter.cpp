/* 
 * File:   CSubSystemFighter.cpp
 * Author: karsten
 * 
 * Created on 24. august 2014, 22:32
 */

#include "CSubSystemFighter.h"

CSubSystemFighter::CSubSystemFighter(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item,uint32_t Xitem):
CSubSystem(owner,slotnode,id){
	
	this->_type = item;
	this->_xItems = 0;
	this->AddItem(Xitem);
	
}

uint32_t CSubSystemFighter::AddItem(uint32_t Xitem){
	if(_xItems > 4)
		cerr<<"WARNING CSubSystemBoost::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	this->_xItems += Xitem;
	return Xitem;
}

uint32_t CSubSystemFighter::RemoveItem(uint32_t Xitem){
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

void CSubSystemFighter::proces(uint32_t DTime){
	_graficCounter+= DTime;
}
bool CSubSystemFighter::isLocking(uint16_t index){
	//if(cooldown(index) <= 0 && _haveTarget && _online && this->_amo >= this->getTypeWep()->getamoCost() && this->getOwner().issubable()->getEnergy() >= this->getTypeWep()->getenegyCost() )
	//	return true;
	return false;
}

CSubSystemFighter::~CSubSystemFighter() {
}

