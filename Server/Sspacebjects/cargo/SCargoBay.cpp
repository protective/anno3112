/* 
 * File:   SCargoBay.cpp
 * Author: karsten
 * 
 * Created on 20. september 2011, 13:12
 */

#include "SCargoBay.h"
#include "../../SItems/SItemType.h"
#include "../SSubAble.h"
#include "../../World/SGrid.h"
#include "../SShip.h"
#include "../../NetworkLayer/SCargoBayNetworkLayer.h"
SCargoBay::SCargoBay(SSubAble* owner, uint32_t maxCargo) {
	this->_owner = owner;
	this->_maxCargo = maxCargo;
	this->_curCargo = 0;
}

uint32_t SCargoBay::AddReturn(SItemType* item, uint32_t quan){
	if (!item)
		cerr<<"ERROR SCargoBay::AddReturn unknown item"<<endl;

	uint32_t freespace = this->_maxCargo - this->_curCargo;

	if (freespace < quan*item->getMass())
		quan = floor(freespace/item->getMass());

	this->_curCargo += quan*item->getMass();

	SCargoI it = this->_content.find(item);
	if (it != this->_content.end())
		this->_content[item] += quan;
	else
		this->_content[item] = quan;

	this->sendCargoUpdate(SubscriptionLevel::lowFreq, item, this->_content[item]);
	if(this->_owner->obj()->isShip() && this->_owner->obj()->isShip()->getOrdres())
		this->_owner->obj()->isShip()->getOrdres()->proces(OrdreEvent::CargoChange,this->_owner->obj());
	return quan;
}


uint32_t SCargoBay::GetAddReturn(SItemType* item, uint32_t quan){
	if (!item)
		cerr<<"ERROR SCargoBay::GetAddReturn unknown item"<<endl;

	uint32_t freespace = this->_maxCargo - this->_curCargo;

	if (freespace < quan*item->getMass())
		quan = floor(freespace/item->getMass());

	return quan;
}


uint32_t SCargoBay::GetReturn(SItemType* item, uint32_t quan){
if (!item)
		cerr<<"ERROR SCargoBay::RemoveReturn unknown item"<<endl;
	//check that we have it
	SCargoI it = this->getContent().find(item);
	if(it != this->_content.end()){
		if (quan > it->second)
			quan = it->second;
	}else
		quan = 0;
	return quan;
}

uint32_t SCargoBay::RemoveReturn(SItemType* item, uint32_t quan){
	if (!item)
		cerr<<"ERROR SCargoBay::RemoveReturn unknown item"<<endl;

	//check that we have it
	SCargoI it = this->getContent().find(item);
	if(it != this->_content.end()){
		if (quan > it->second)
			quan = it->second;
	}else
		quan = 0;
	
	this->_content[item] -= quan;
	this->_curCargo -= quan*item->getMass();
	this->sendCargoUpdate(SubscriptionLevel::lowFreq,item,this->_content[item]);
	if(this->_owner->obj()->isShip() && this->_owner->obj()->isShip()->getOrdres())
		this->_owner->obj()->isShip()->getOrdres()->proces(OrdreEvent::CargoChange,this->_owner->obj());
	return quan;
}

uint32_t SCargoBay::TransfereCargo(SCargoBay* bay,SItemType* item, uint32_t quan){
	if (!item)
		cerr<<"ERROR SCargoBay::TransfereCargo unknown item"<<endl;
	//quan = this->GetReturn(item,quan);

	quan = bay->AddReturn(item,RemoveReturn(item,bay->GetAddReturn(item,quan)));
	
	this->sendCargoUpdate(SubscriptionLevel::lowFreq,item,this->_content[item]);
	bay->sendCargoUpdate(SubscriptionLevel::lowFreq,item,bay->getContent()[item]);
	return quan;
}

void SCargoBay::sendCargoUpdate(SubscriptionLevel::Enum level, SItemType* item, uint32_t quan){
	SendCargoUpdate(this->getOwner()->obj()->getSubscribers()[level],this->getOwner(), item, quan);
}

SCargoBay::~SCargoBay() {
}

