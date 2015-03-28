/* 
 * File:   SSingleWep.cpp
 * Author: karsten
 * 
 * Created on 1. juli 2011, 21:26
 */

#include "SSingleWep.h"
#include "SSubSystemW.h"
#include "../SSubAble.h"
#include "../SShip.h"
#include "../SShot.h"
#include "../../World/SGrid.h"
#include "../../World/SWorld.h"
#include "../SMetaObj.h"
#include "../../Commands/CommandEnterGrid.h"

SSingleWep::SSingleWep(SSubSystemW* subsys) {
	this->subsys = subsys;
	this->_cur = -1;
	this->_charge = 1;
	_lockingPower = 0;
}

void SSingleWep::proces(Processor* processor){
	if(_lockingPower< 100000)
		_lockingPower++;
	if (this->subsys->getOwner().getsubable() == NULL){
		cerr<<"WARNING SingleWep::proces Not Subable"<<endl;
		return;
	}

	if(this->_cur == 0){
		this->_charge = 1;
		this->resetLockPower();
		this->_cur = -1;
	}
	bool countrecoil = false;
	
	if(this->subsys->getOwner().isShip() && this->subsys->getTypeWep()->getRecoil() >= this->subsys->getOwner().isShip()->getShipType()->getRecoilRecharge()*3)
		countrecoil = true;
	
	if(this->_charge > 0 && (!countrecoil || this->subsys->getOwner().getsubable()->getRecoil() == this->subsys->getOwner().getsubable()->getMaxRecoil()) && this->subsys->online() && (!this->subsys->recharge() || this->subsys->getTypeWep()->getAmoCostType() == NULL) && this->subsys->getfireseq() == this->subsys->getTypeWep()->getmaxseq()){
		if (this->subsys->getTarget()){
			if(getLockPower() >= this->subsys->getlockingAgainstPower()){//caculate locking power 
				this->subsys->setfireseq(0); 
				this->_tempseq = this->subsys->getTypeWep()->fireseq();
				this->subsys->setSeqTarget(this->subsys->getOwner().getsubable()->getNextTarget(processor, this->subsys->getSlotNode()));
				this->_charge-=1;
				if(countrecoil)
					this->subsys->getOwner().getsubable()->useRecoil(this->subsys->getTypeWep()->getRecoil());
			}
		}
	}
	if (this->subsys->getSeqTarget() && this->subsys->getfireseq() < this->subsys->getTypeWep()->getmaxseq()){
		list<uint32_t>::iterator it = this->_tempseq.begin();
		
		if (it != this->_tempseq.end() && (*it) == this->subsys->getfireseq()){
			this->_tempseq.pop_front();
			this->subsys->setSeqTarget(this->subsys->getOwner().getsubable()->getNextTarget(processor, this->subsys->getSlotNode()));
	
			SMetaObj* tempMeta = processor->getMeta(this->subsys->getSeqTarget());
			if(tempMeta){
				SPos tempTargetPos = tempMeta->pos;
				int32_t temp = Direction(this->subsys->getOwner().getPos(),tempTargetPos)-(this->subsys->getOwner().getPos().d/100) ;
				if(temp < 0) temp+=360;
				if(InAngle(temp,this->subsys->getSlotNode()->getST()->getFireDir())){//TODO fix
					SPos* owner = &this->subsys->getOwner().getPos();
					int32_t x = owner->x+ ((this->subsys->getSlotNode()->getST()->gX()*(VektorUnitX(owner->d/100)) + (this->subsys->getSlotNode()->getST()->gY()*(VektorUnitY(owner->d/100)))));
					int32_t y = owner->y+ ((this->subsys->getSlotNode()->getST()->gX()*(-VektorUnitY(owner->d/100)) + (this->subsys->getSlotNode()->getST()->gY()*(VektorUnitX(owner->d/100)))));
					SPos temppos(x,y,0);
					processor->createShot(temppos,this->subsys->getOwner().getsubable(), this->subsys->getSeqTarget(), this->subsys->getTypeWep());
					
					if(this->subsys->getOwner().isShip())
						this->subsys->getOwner().isShip()->ResetLastCombat();
				}
			}
		}
	}
	
	
	if(this->_cur <= 0 && this->_charge == 0){
		if (this->subsys->online() && (!this->subsys->recharge()) || this->subsys->getTypeWep()->getAmoCostType() == NULL){
			if(this->subsys->getTypeWep()->getamoCost() <= this->subsys->getAmo()){
				if (this->subsys->getTypeWep()->getenegyCost() <= this->subsys->getOwner().getsubable()->getEnergy()){
					this->_cur = this->subsys->getTypeWep()->getMaxCd();
					this->subsys->useAmo(this->subsys->getTypeWep()->getamoCost());
					this->subsys->getOwner().getsubable()->useEnergy(this->subsys->getTypeWep()->getenegyCost());
					this->subsys->reportCharge(SubscriptionLevel::details);
					if(this->subsys->getTypeWep()->getamoCost() > this->subsys->getAmo())
						this->subsys->setRecharge(true);
				}
			}
				
		}
		this->subsys->getOwner();
		subsys->getTypeWep()->getMaxCd();

	}else if(this->_cur > 0){
		
		this->_cur -= 1000/FRAMERATE; //TODO add dmg here
		if (this->_cur < 0)
			this->_cur = 0;
	}

}




SSingleWep::~SSingleWep() {
}

