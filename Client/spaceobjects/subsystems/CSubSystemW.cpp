/* 
 * File:   CSubSystemW.cpp
 * Author: karsten
 * 
 * Created on 31. juli 2011, 23:45
 */

#include "CSubSystemW.h"
#include "../CSubAble.h"
CSubSystemW::CSubSystemW(CObj& owner,CSlotNode& slotnode,uint32_t id,CItemType* item, uint32_t Xitem):
CSubSystem(owner,slotnode,id)
{
	this->_type = item;
	this->_xItems = 0;
	this->AddItem(Xitem);
	
}

void CSubSystemW::proces(uint32_t DTime){
	_graficCounter+= DTime;
	for(CSingleWI it = _weps.begin();it != _weps.end(); it++){
		it->second->proces(DTime);
	}
}
bool CSubSystemW::isLocking(uint16_t index){
	if(cooldown(index) <= 0 && _haveTarget && _online && this->_amo >= this->getTypeWep()->getamoCost() && this->getOwner().issubable()->getEnergy() >= this->getTypeWep()->getenegyCost() )
		return true;
	return false;
}

uint32_t CSubSystemW::AddItem(uint32_t Xitem){
	if(_xItems > 4)
		cerr<<"WARNING subsystemw::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_weps[i] = new CSingleWep(this);
	}
	this->_xItems += Xitem;
	return Xitem;
}

uint32_t CSubSystemW::RemoveItem(uint32_t Xitem){
	cerr<<"Xitem"<<Xitem<<endl;
	if(_xItems >= Xitem){
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_weps[i-1];
			this->_weps.erase(i-1);
		}
		_xItems = _xItems - Xitem;
		return Xitem;
	}else{
		Xitem = _xItems;
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_weps[i-1];
			this->_weps.erase(i-1);
		}
		_xItems = 0;
		return Xitem;
	}
	return Xitem;
}


CSubSystemW::~CSubSystemW() {
}

