/* 
 * File:   SSubSystemFac.cpp
 * Author: karsten
 * 
 * Created on 15. september 2011, 09:39
 */

#include "SSubSystemFac.h"
#include "../cargo/SCargoBay.h"
#include "../SSubAble.h"
SSubSystemFac::SSubSystemFac(SObj& owner,SSlotNode& slotnode, uint32_t id, SItemType* item, uint32_t Xitem):
SSubSystem(owner,slotnode,id)
{
	this->_xItems = 0;
	this->_type = item;

	this->AddItem(Xitem);
	this->setOnline(true);
}

void SSubSystemFac::proces(Processor* processor){
	bool buildnext = true;
	for(SSingleFacI it = _fac.begin();it != _fac.end(); it++){
		if (it->second->getDuration() != -1)
			buildnext = false;
	}
	
	if (buildnext){
		if (this->_queue.size()){
			this->_curentBuild = this->_queue.front()._item;
		}else
			this->_curentBuild = NULL;
		
		if (this->_curentBuild){
			this->_maxcooldown = this->_curentBuild->getBuildTime();
		}else
			this->_maxcooldown = 0;
		
	}

	for(SSingleFacI it = _fac.begin();it != _fac.end(); it++){
		it->second->proces(processor);
	}


}

uint32_t SSubSystemFac::buildItem(SItemType* item, uint32_t quantity){
	if (item){
		bool canbuild = true;
		SCargoBay* cargo = this->getOwner().getsubable()->getCargoBay();
		if (cargo && quantity){
			for(map<uint32_t,bmaterial>::iterator it = item->getCost().begin(); it != item->getCost().end(); it++){
				if (it->second._quan*quantity > cargo->GetReturn(itemlist[it->first],it->second._quan*quantity)){
					canbuild = false;
					break;
				}
			}
		
			if (canbuild){
				for(map<uint32_t,bmaterial>::iterator it = item->getCost().begin(); it != item->getCost().end(); it++){
					cargo->RemoveReturn(itemlist[it->first],it->second._quan*quantity);
				}
				SSubSystemFacQueue temp;
				temp._item = item;
				temp._quantity = quantity;
				this->_queue.push_back(temp);
			}
		}
	}else
		cerr<<"WARNING SSubSystemFac::buildItem unknown item- no build done"<<endl;

	

}

uint32_t SSubSystemFac::AddItem(uint32_t Xitem){

	if(this->_type->getSubType()->getMount() * (_xItems+Xitem) > this->_slotnode->getST()->slotMount()){
		if(this->_type->getSubType()->getMount())
			Xitem = (this->_slotnode->getST()->slotMount()/this->_type->getSubType()->getMount()) -_xItems;
		else
			Xitem = 0;
	}
	
	if(_xItems > 4)
		cerr<<"WARNING subsystemfac::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_fac[i] = new SSingleFac(this);
	}
	this->_xItems += Xitem;
	return Xitem;

}

uint32_t SSubSystemFac::RemoveItem(uint32_t Xitem){
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

SSubSystemFac::~SSubSystemFac() {
}

