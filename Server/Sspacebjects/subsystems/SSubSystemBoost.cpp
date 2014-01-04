/* 
 * File:   SSubSystemBoost.cpp
 * Author: karsten
 * 
 * Created on 24. december 2011, 12:05
 */

#include "SSubSystemBoost.h"
#include "../SSubAble.h"
#include "../../World/SGrid.h"
SSubSystemBoost::SSubSystemBoost(SObj& owner,SSlotNode& slotnode,uint32_t id,SItemType* item, uint32_t Xitem):
SSubSystemBonus(owner,slotnode,id,item,Xitem){
	
	this->_rechargeCounter = 0;
	this->_maxcooldown = this->getTypeBoost()->getMaxCd();
	this->_cooldown = 0;
	this->addAmo(100000);
	this->setOnline(true);
	this->setRecharge(true);
}

uint32_t SSubSystemBoost::addAmo(uint32_t amo){
	if (this->_amo + amo <= this->getMaxAmo()){
		this->_amo+= amo;
		return amo;
	}else{
		amo = this->getMaxAmo()- this->_amo;
		this->_amo = this->getMaxAmo();
		return amo;
	}

}


uint32_t SSubSystemBoost::useAmo(uint32_t amo){
	if(this->_amo >= amo){
		this->_amo -= amo;
		return amo;
	}else{
		amo -= this->_amo;
		this->_amo = 0;
		return amo;
	}
}

void SSubSystemBoost::proces(){


	if(this->_cooldown == 0){
		this->_charge = 1;
		this->_cooldown = -1;
	}
	if(this->_charge > 0 && this->online()){
		bool boostNow = false;
		if(this->_owner->getsubable()){
			uint32_t threshold = 1000;
			if (this->_owner->IsOutOfCombat())
				threshold = 10;
			switch (this->getTypeBoost()->getBoostType()){
				case BonusTypes::Armor:{
					if(this->_owner->getsubable()->getArmor() + (threshold * this->getTypeBoost()->getBoostAmount()*_xItems) < this->_owner->getsubable()->getMaxArmor() ){
						this->_owner->getsubable()->AddArmor(1000 * this->getTypeBoost()->getBoostAmount()*_xItems);
						boostNow = true;
						
					}
					break;
				}
				case BonusTypes::Hull:{
					if(this->_owner->getsubable()->getHull() + (threshold * this->getTypeBoost()->getBoostAmount()*_xItems) < this->_owner->getsubable()->getMaxHull()){
						this->_owner->getsubable()->AddHull(1000 * this->getTypeBoost()->getBoostAmount()*_xItems);
						boostNow = true;
						
					}
					break;
				}
				case BonusTypes::Deflector:{
					if(this->_owner->getsubable()->getDeflector() + (threshold * this->getTypeBoost()->getBoostAmount()*_xItems) < this->_owner->getsubable()->getMaxDeflector()){
						this->_owner->getsubable()->AddDeflector(1000 * this->getTypeBoost()->getBoostAmount()*_xItems);
						boostNow = true;
						
					}
					break;
				}
				case BonusTypes::ShieldStr:{
					double l = 1;
					int j = -1;
					for(uint32_t i = 0 ; i < 6; i++){
						if(this->_owner->getsubable()->getMaxShield(i)){
							double k = (double)this->_owner->getsubable()->getShield(i)/this->_owner->getsubable()->getMaxShield(i);
							if (k < l){
								j = i;
								l = k;
							}
						}
					}
					if(j >= 0){
						if(this->_owner->getsubable()->getShield(j) + (threshold * this->getTypeBoost()->getBoostAmount()*_xItems) < this->_owner->getsubable()->getMaxShield(j)){
							this->_owner->getsubable()->AddShield(j,1000 * this->getTypeBoost()->getBoostAmount()*_xItems);
							boostNow = true;
						}
					}
					break;
				}
			}
			if(boostNow)
				this->getOwner().getPos().grid->BroadCastReportObjHpUdate(this->_owner);

		}
		if(boostNow)
			this->_charge-=1;
	}

	if(this->_cooldown <= 0 && this->_charge == 0){
		if (this->online() ){
			if(this->getTypeBoost()->getamoCost() *_xItems <= this->getAmo()){
				if (this->getTypeBoost()->getenegyCost()*_xItems <= this->getOwner().getsubable()->getEnergy()){
					this->_cooldown = this->getTypeBoost()->getMaxCd();
					this->useAmo(this->getTypeBoost()->getamoCost()*_xItems);
					this->getOwner().getsubable()->useEnergy(this->getTypeBoost()->getenegyCost()*_xItems);
					this->getOwner().getPos().grid->ReportCharge(this,false);
				}//else
				//	cerr<<"out of ener"<<endl;
			}//else
			//	cerr<<"out of amo"<<endl;
		}

	}else if(this->_cooldown > 0){

		this->_cooldown -= 1000/FRAMERATE; //TODO add dmg here
		if (this->_cooldown < 0)
			this->_cooldown = 0;
	}



	this->_rechargeCounter++;
	if(this->_rechargeCounter >= 25){
		this->_rechargeCounter = 0;
		if (this->_amo < this->getMaxAmo()){
			if(this->getTypeBoost()->getAmoCostType() == NULL ){
				if (this->_recharge)
					this->addAmo(this->_owner->getsubable()->useEnergy(this->getTypeBoost()->getAmoRechargeRate()*_xItems));
			}else if(this->_recharge){
				uint32_t a = this->getTypeBoost()->getAmoRechargeRate() *_xItems;
				if( this->_amo -this->getMaxAmo() < a)
					a = this->_amo -this->getMaxAmo();
				uint32_t toadd = this->_owner->getsubable()->getCargoBay()->RemoveReturn(this->getTypeBoost()->getAmoCostType(),a);
				if (toadd)
					this->addAmo(toadd);
				else
					_recharge = false;
			}
			this->getOwner().getPos().grid->ReportCharge(this,false);

		}else if(_recharge) {
			//_recharge = false;
			//this->getOwner().getPos().grid->ReportCharge(this);
		}
	}
}



SSubSystemBoost::~SSubSystemBoost() {
}

