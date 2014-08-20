/* 
 * File:   SSubSystemFighter.cpp
 * Author: karsten
 * 
 * Created on 4. februar 2014, 19:57
 */

#include "SSubSystemFighter.h"
#include "SSubTypeFighter.h"
#include "../SFighter.h"
#include "../SShip.h"
#include "../../World/SWorld.h"
SSubSystemFighter::SSubSystemFighter(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem):
SSubSystem(owner,slotnode,id)
{
	_type = item;
	cerr<<"_type ="<<_type<<endl;
	cerr<<"_type ="<<_type->getSubType()<<endl;
	cerr<<"_type ="<<_type->getSubType()->isFighter()<<endl;
	cerr<<"type ="<<getTypeFighter()<<endl;
	cerr<<"type ="<<getTypeFighter()->getFighterType()<<endl;
	this->_xItems = 0;
	_cur = 0;
	_lockingPower = 0;
	_charge = 1;
	_online = true;
	this->AddItem(Xitem);
	//this->_rechargeCounter = 0;
	this->_targetGroup = TargetGroup::Heavy;
	//this->_target = 0;
	//this->_seqTarget = 0;
	//this->_maxcooldown = this->getTypeWep()->getMaxCd();
	//this->_fireseq = this->getTypeWep()->getmaxseq();
	
	cerr<<"create subsystem fighter"<<endl;

	cerr<<"done create subsystem fighter"<<endl;
}

void SSubSystemFighter::proces(Processor* processor){
		if(_lockingPower< 100000)
		_lockingPower++;
	if (this->getOwner().getsubable() == NULL){
		cerr<<"WARNING SingleWep::proces Not Subable"<<endl;
		return;
	}

	if(this->_cur == 0){
		this->_charge = 1;
		//this->resetLockPower();
		this->_cur = -1;
	}
	bool countrecoil = false;
	
	
	countrecoil = true;
	if(this->_charge > 0 &&  this->online() ){
		if (this->getTarget()){
			//if(getLockPower() >= this->getlockingAgainstPower()){//caculate locking power 
			//	this->setfireseq(0); 
			//	this->_tempseq = this->getTypeWep()->fireseq();
			//	this->setSeqTarget(this->getTarget());
			cerr<<"launch fighter"<<endl;
			this->launchFighter();
			cerr<<"done launch fighers"<<endl;
			this->_charge-=1;
			//	if(countrecoil)
			//		this->getOwner().getsubable()->useRecoil(this->getTypeWep()->getRecoil());
			//}
		}
	}
	
	if(this->_cur <= 0 && this->_charge == 0){
		if (this->online()){
			if(this->getTypeFighter()->getamoCost() <= this->getAmo()){
				//if (this-->getTypeFighter()->getenegyCost() <= this->getOwner().getsubable()->getEnergy()){
					this->_cur = this->getTypeFighter()->getMaxCd();
					//this->useAmo(this->getTypeWep()->getamoCost());
					//this->getOwner().getsubable()->useEnergy(this->getTypeWep()->getenegyCost());
					this->reportCharge(SubscriptionLevel::details);
					//if(this->getTypeFighter()->getamoCost() > this->subsys->getAmo())
					//	this->setRecharge(true);
				//}
			}
				
		}
		
		//subsys->getTypeWep()->getMaxCd();

	}else if(this->_cur > 0){
		
		this->_cur -= 1000/FRAMERATE; //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}
}

uint32_t SSubSystemFighter::AddItem(uint32_t Xitem){
	_xItems += Xitem;
	Xitem *= getTypeFighter()->getBayCount();
	Xitem = min(Xitem, (uint32_t)max((int32_t)0, (int32_t)(_xItems*getTypeFighter()->getBayCount()) - (int32_t)_fightersLunchTImer.size()));
	while (Xitem> 0){
		uint32_t tid= 1; //unit can never have id 0
		for(map<uint32_t, uint32_t>::iterator it = _fightersLunchTImer.begin(); it != _fightersLunchTImer.end(); it++){
			if(it->first >= tid)
				tid = it->first + 1;
		}
		_fightersLunchTImer[tid] = 10000;
		Xitem--;
	}
}

uint32_t SSubSystemFighter::RemoveItem(uint32_t Xitem){

}

void SSubSystemFighter::launchFighter(){
	uint32_t id = 0;
	for(map<uint32_t, uint32_t>::iterator it = _fightersLunchTImer.begin(); it != _fightersLunchTImer.end(); it++){
		if(it->second == 10000){
			id = it->first;
			break;
		}
	}
	if(id== 0)
		return;
	
	SPos* temppos =  &this->getOwner().getPos();
	
	cerr<<"pos grid ="<<temppos->grid<<endl;
	this->_owner->isShip()->getProcessor()->createFighter(*temppos, *getTypeFighter()->getFighterType(),this->getOwner().getPlayerId());
	_fightersLunchTImer[id] = 0;

}

void SSubSystemFighter::recoverFighter(uint32_t id){

}

void SSubSystemFighter::resetLockPower(){

}

SSubSystemFighter::~SSubSystemFighter() {
}
