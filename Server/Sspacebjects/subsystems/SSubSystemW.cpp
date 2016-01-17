/* 
 * File:   SSubSystemW.cpp
 * Author: karsten
 * 
 * Created on 25. juni 2011, 01:44
 */

#include "SSubSystemW.h"
#include "../SSubAble.h"
#include "../SUnit.h"
#include "../SMetaObj.h"
#include "../../World/SGrid.h"

SSubSystemW::SSubSystemW(SObj& owner,SSlotNode& slotnode,uint32_t id ,SItemType* item,uint32_t Xitem):
SSubSystem(owner,slotnode,id)
{
	this->_type = item;
	this->_xItems = 0;
	this->AddItem(Xitem);
	
	this->_rechargeCounter = 0;
	this->_targetGroup = TargetGroup::Heavy;
	this->_target = 0;
	this->_seqTarget = 0;
	this->_maxcooldown = this->getTypeWep()->getMaxCd();
	this->_fireseq = this->getTypeWep()->getmaxseq();



	this->addAmo(100000);
	this->setOnline(true);
	if(this->getTypeWep()->getAmoCostType() == NULL)
		this->setRecharge(true);
	else
		this->setRecharge(false);
}

void SSubSystemW::resetLockPower(){
	reset();
	for(map<uint32_t,SSingleWep*>::iterator it = _weps.begin(); it != _weps.end();it++){it->second->resetLockPower();}
	if(!this->getTarget())
		this->reportCharge(SubscriptionLevel::details);
}

void SSubSystemW::reset(){
	
	//TODO FIX
	
	if(this->getTarget()){
		double res = (double)this->getTypeWep()->getResolution(getOwner().getsubable()->getBonusList());
		uint32_t size = this->getOwner().getPos().grid->getMetaInGrid(this->getTarget())->getTargetSize();
		double sig = size/100;
		if(res <= sig)
			_lockingAgainstPower = 0;
		else
			_lockingAgainstPower = (pow((res-sig)/10,1.5)*this->getTypeWep()->getMaxCd())/1000;
	}else{
		_lockingAgainstPower = 0;

	}
	
}

void SSubSystemW::announceRemovalOf(SObj* obj){
		//TODO FIX
	/*

	if (_target && obj == _target->obj())
		_target = NULL;
	if(_seqTarget && obj == _seqTarget->obj())
		_seqTarget = NULL;
	 
	 */
}

uint32_t SSubSystemW::addAmo(uint32_t amo){
	if (this->_amo + amo <= this->getMaxAmo()){
		this->_amo+= amo;
		return amo;
	}else{
		amo = this->getMaxAmo()- this->_amo;
		this->_amo = this->getMaxAmo();
		return amo;
	}
	
}


uint32_t SSubSystemW::useAmo(uint32_t amo){
	if(this->_amo >= amo){
		this->_amo -= amo;
		return amo;
	}else{
		amo -= this->_amo;
		this->_amo = 0;
		return amo;
	}
}

void SSubSystemW::proces(Processor* processor){

	if (this->_fireseq < this->getTypeWep()->getmaxseq())
		this->_fireseq++;

	for(SSingleWI it = _weps.begin();it != _weps.end(); it++){
		it->second->proces(processor);
	}

	this->_rechargeCounter++;
	if(this->_rechargeCounter >= 25){
		this->_rechargeCounter = 0;
		if (this->_amo < this->getMaxAmo()){
			if(this->getTypeWep()->getAmoCostType() == NULL){
				if (this->_recharge)
					this->addAmo(this->_owner->getsubable()->useEnergy(this->getTypeWep()->getAmoRechargeRate()*_xItems));
			}else if(this->_recharge){
				uint32_t a = this->getTypeWep()->getAmoRechargeRate()*_xItems;
				if( this->_amo -this->getMaxAmo() < a)
					a = this->_amo -this->getMaxAmo();
				uint32_t toadd = this->_owner->getsubable()->getCargoBay()->RemoveReturn(this->getTypeWep()->getAmoCostType(),a);
				if (toadd)
					this->addAmo(toadd);
				else
					_recharge = false;
			}
			this->reportCharge(SubscriptionLevel::details);

		}else if(_recharge && this->getTypeWep()->getAmoCostType() != NULL) {
			_recharge = false;
			this->reportCharge(SubscriptionLevel::details);
		}
	}
}

uint32_t SSubSystemW::AddItem(uint32_t Xitem){

	if(this->_type->getSubType()->getMount() * (_xItems+Xitem) > this->_slotnode->getST()->slotMount()){
		if(this->_type->getSubType()->getMount())
			Xitem = (this->_slotnode->getST()->slotMount()/this->_type->getSubType()->getMount()) -_xItems;
		else
			Xitem = 0;
	}
	if(_xItems > 4)
		cerr<<"WARNING subsystemw::addItem xitem out of range "<<_xItems<<endl;
	if (_xItems + Xitem > 4){
		Xitem = 4 - _xItems;
	}
	for(uint32_t i = _xItems; i < _xItems+Xitem; i++){
		this->_weps[i] = new SSingleWep(this);
	}
	this->_xItems += Xitem;
	return Xitem;
	
}
uint32_t SSubSystemW::RemoveItem(uint32_t Xitem){
	cerr<<"Xitem"<<Xitem<<endl;
	if(_xItems >= Xitem){
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_weps[i-1];
			this->_weps.erase(i-1);
		}
		_xItems = _xItems - Xitem;
		if (this->_amo > this->getMaxAmo())
			this->_amo = this->getMaxAmo();

		return Xitem;
	}else{
		Xitem = _xItems;
		for(int32_t i = _xItems; i > _xItems-Xitem; i--){
			cerr<<"delete item i="<<i-1<<endl;
			delete this->_weps[i-1];
			this->_weps.erase(i-1);
		}
		_xItems = 0;
		if (this->_amo > this->getMaxAmo())
			this->_amo = this->getMaxAmo();
		return Xitem;
	}
	return Xitem;
}


SSubSystemW::~SSubSystemW() {
}

