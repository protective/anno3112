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
#include "../../Commands/CargoCommands/CommandCargoTransfere.h"
#include "../../Commands/CargoCommands/CommandCargoTransOnReciver.h"
#include "../../NetworkLayer/SCargoBayNetworkLayer.h"
SCargoBay::SCargoBay(SSubAble* owner, uint32_t maxCargo) {
	this->_owner = owner;
	this->_maxCargo = maxCargo;
	this->_curCargo = 0;
	this->_procesTimer = 0;
	this->_outgoingCredit = 0;
	this->_incommingCredit = 0;
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
uint32_t SCargoBay::GetCur(uint32_t id){
	if(itemlist.find(id) != itemlist.end())
		return _content[itemlist[id]];
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

void SCargoBay::sendCargoBay(list<uint32_t>& clients){
	SendCargoUpdate(clients, this);
}

uint32_t SCargoBay::sendItem(uint32_t toShip, uint32_t item, uint32_t quan) {
	
}
 
void SCargoBay::proces(uint32_t deltaT){
	_procesTimer += deltaT;

	if(_procesTimer > 1000){
		_procesTimer -= 1000;
		_outgoingCredit = 150;
		_incommingCredit = 150;
		//addIncommingCredit(10);
		//addOutgoingCredit(10);
		for(map<uint32_t, transfereOperation>::iterator it =  _transferes.begin(); it != _transferes.end(); ){
			

			if(it->second._remaning > 0 && _outgoingCredit > 0){
				SItemType* item = itemlist[it->second._itemId];
				
				
				if(GetCur(it->second._itemId) < it->second._remaning)
					it->second._remaning = GetCur(it->second._itemId);
				
				uint32_t remaning = it->second._remaning;
				uint32_t count = 0;
				//cerr<<"out credit="<<_outgoingCredit<< "mass ="<<item->getMass()<<endl;
				
				uint32_t mass = max((uint32_t)1, item->getMass());
				if(_outgoingCredit >= mass * remaning){
					count = remaning;
					_outgoingCredit -= mass * remaning;
				}else if(_outgoingCredit >= mass){
					count =  _outgoingCredit / mass;
					_outgoingCredit -= (mass * count);
				}
				if(count){
					it->second._remaning -= count;
					RemoveReturn(item, count);
					CommandCargoTransOnReciver* cmd;
					cmd = new CommandCargoTransOnReciver(it->second._id, _owner->obj()->getId(), it->second._toId, it->second._itemId, count);

					if (networkControl->addCommandToProcesable(cmd,it->second._toId))
						delete cmd;
				}	
			}
			
			if(it->second._remaning == 0)
				_transferes.erase(it++);
			else
				it++;
			
		}
		
	}
	
}

void SCargoBay::addTransfere(uint32_t toShipId, uint32_t itemType, uint32_t quan){
	
	
	transfereOperation t;
	int i = 0;
	while( _transferes.find(i) != _transferes.end()){
		i++;
	}

	t._id = i;
	t._itemId = itemType;
	t._remaning = quan;
	t._toId = toShipId;
	_transferes[i] = t;
}


SCargoBay::~SCargoBay() {
}

