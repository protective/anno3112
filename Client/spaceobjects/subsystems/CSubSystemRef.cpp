/* 
 * File:   CSubSystemRef.cpp
 * Author: karsten
 * 
 * Created on 23. marts 2012, 23:23
 */

#include "CSubSystemRef.h"

CSubSystemRef::CSubSystemRef(CObj& owner,CSlotNode& slotnode,uint32_t id, CItemType* item, uint32_t Xitem):
CSubSystem(owner,slotnode,id) {
	this->_xItems = 0;
	this->_type = item;

	this->AddItem(Xitem);
	this->setOnline(true);
}

void CSubSystemRef::proces(uint32_t DTime){
	_graficCounter+= DTime;
	for(CSingleRefI it = _ref.begin();it != _ref.end(); it++){
		it->second->proces(DTime);
	}
}

uint32_t CSubSystemRef::AddItem(uint32_t Xitem){
	if(_xItems > 4)
		cerr<<"WARNING CSubSystemRef::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_ref[i] = new CSingleRef(this);
	}
	this->_xItems += Xitem;
	return Xitem;
}

uint32_t CSubSystemRef::RemoveItem(uint32_t Xitem){
	cerr<<"Xitem"<<Xitem<<endl;
	if(_xItems >= Xitem){
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_ref[i-1];
			this->_ref.erase(i-1);
		}
		_xItems = _xItems - Xitem;
		return Xitem;
	}else{
		Xitem = _xItems;
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_ref[i-1];
			this->_ref.erase(i-1);
		}
		_xItems = 0;
		return Xitem;
	}
	return Xitem;
}

CSubSystemRef::~CSubSystemRef() {
}

