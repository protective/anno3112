/* 
 * File:   CSubSystemFac.cpp
 * Author: karsten
 * 
 * Created on 16. september 2011, 21:31
 */

#include "CSubSystemFac.h"
#include "../CSubAble.h"

CSubSystemFac::CSubSystemFac(CObj& owner,CSlotNode& slotnode,uint32_t id, CItemType* item, uint32_t Xitem):
CSubSystem(owner,slotnode,id) {
	this->_xItems = 0;
	this->_type = item;

	this->AddItem(Xitem);
	this->setOnline(true);
}

bool CSubSystemFac::haveEnoughTobuild(CItemType* item){
	if(this->getOwner().issubable()){
		for (map<uint32_t,bmaterial>::iterator it = item->getCost().begin(); it != item->getCost().end(); it++){
			uint32_t have = 0;
			if (it->second._item){
				have = this->getOwner().issubable()->getCargoBay()->GetReturn(it->second._item,0-1);
				if(have < it->second._quan)		
					return false;
			}
		}
		return true;
	}else
		return false;
}

void CSubSystemFac::proces(uint32_t DTime){
	_graficCounter+= DTime;
	for(CSingleFacI it = _fac.begin();it != _fac.end(); it++){
		it->second->proces(DTime);
	}
}

uint32_t CSubSystemFac::AddItem(uint32_t Xitem){
	if(_xItems > 4)
		cerr<<"WARNING CSubSystemFac::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_fac[i] = new CSingleFac(this);
	}
	this->_xItems += Xitem;
	return Xitem;
}

uint32_t CSubSystemFac::RemoveItem(uint32_t Xitem){
	cerr<<"Xitem"<<Xitem<<endl;
	if(_xItems >= Xitem){
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_fac[i-1];
			this->_fac.erase(i-1);
		}
		_xItems = _xItems - Xitem;
		return Xitem;
	}else{
		Xitem = _xItems;
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_fac[i-1];
			this->_fac.erase(i-1);
		}
		_xItems = 0;
		return Xitem;
	}
	return Xitem;
}


CSubSystemFac::~CSubSystemFac() {
}

