/* 
 * File:   SSubSystemBonus.cpp
 * Author: karsten
 * 
 * Created on 24. december 2011, 12:05
 */

#include "SSubSystemBonus.h"
#include "../SSubAble.h"
SSubSystemBonus::SSubSystemBonus(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem):
SSubSystem(owner,slotnode,id){
	this->_type = item;
	this->_xItems = 0;
	this->setOnline(true);
	this->AddItem(Xitem);


}

void SSubSystemBonus::procesBonus(SSubAble* obj){
	for(map<BonusTypes::Enum, int32_t>::iterator it = this->getTypeBonus()->getBonuslist().begin(); it != this->getTypeBonus()->getBonuslist().end(); it++){
		obj->getBonusList()[it->first]+= (1000*it->second * _xItems);
	}
}


uint32_t SSubSystemBonus::AddItem(uint32_t Xitem){

	if(this->_type->getSubType()->getMount() * (_xItems+Xitem) > this->_slotnode->getST()->slotMount()){
		if(this->_type->getSubType()->getMount())
			Xitem = (this->_slotnode->getST()->slotMount()/this->_type->getSubType()->getMount()) -_xItems;
		else
			Xitem = 0;
	}

	if(_xItems > 4)
		cerr<<"WARNING SSubSystemBonus::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	this->_xItems += Xitem;
	return Xitem;
}


uint32_t SSubSystemBonus::RemoveItem(uint32_t Xitem){
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

SSubSystemBonus::~SSubSystemBonus() {
}

