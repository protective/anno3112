/* 
 * File:   SSubSystemRef.cpp
 * Author: karsten
 * 
 * Created on 23. marts 2012, 23:22
 */

#include "SSubSystemRef.h"
#include "../cargo/SCargoBay.h"
#include "../SSubAble.h"
SSubSystemRef::SSubSystemRef(SObj& owner,SSlotNode& slotnode, uint32_t id, SItemType* item, uint32_t Xitem):
SSubSystem(owner,slotnode,id)
{
	this->_xItems = 0;
	this->_type = item;

	if(item && item->getSubType() && item->getSubType()->isRef()){
		for(map<uint32_t,SItemType*>::iterator it = item->getSubType()->isRef()->getCanRefineList().begin(); it != item->getSubType()->isRef()->getCanRefineList().end(); it++){
			this->_refinequeue.push_back(it->second);
		}
	}

	this->AddItem(Xitem);
	this->setOnline(true);
}

void SSubSystemRef::proces(Processor* processor){
	if(_online){
		for(SSingleRefI it = _ref.begin();it != _ref.end(); it++){
			if (it->second->getDuration() == -1){
				if(this->_refinequeue.size() > 0){
					SItemType* item = this->_refinequeue.front();
					if (item && item->getRefineBatch() > 0){
						SCargoBay* cargo = this->getOwner().getsubable()->getCargoBay();
						if (cargo){
							if (item->getRefineBatch() <= cargo->GetReturn(item,item->getRefineBatch())){
								cerr<<"begin refine"<<endl;
								cargo->RemoveReturn(item,item->getRefineBatch());
								it->second->Refine(item);
							}
						}
					}else{
						cerr<<"WARNING SSubSystemRef::refineItem unknown or invalid item- no refine done"<<endl;
					}
					this->_refinequeue.push_back(this->_refinequeue.front());
					this->_refinequeue.pop_front();
				}
			}
		}
	}
	for(SSingleRefI it = _ref.begin();it != _ref.end(); it++){
		it->second->proces(processor);
	}
}

uint32_t SSubSystemRef::AddItem(uint32_t Xitem){

	if(this->_type->getSubType()->getMount() * (_xItems+Xitem) > this->_slotnode->getST()->slotMount()){
		if(this->_type->getSubType()->getMount())
			Xitem = (this->_slotnode->getST()->slotMount()/this->_type->getSubType()->getMount()) -_xItems;
		else
			Xitem = 0;
	}

	if(_xItems > 4)
		cerr<<"WARNING SSubSystemRef::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_ref[i] = new SSingleRef(this);
	}
	this->_xItems += Xitem;
	return Xitem;

}

uint32_t SSubSystemRef::RemoveItem(uint32_t Xitem){
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
SSubSystemRef::~SSubSystemRef() {
}

