/* 
 * File:   SAstoroid.cpp
 * Author: karsten
 * 
 * Created on 5. oktober 2011, 20:39
 */

#include "SAstoroid.h"
#include "SShot.h"
#include "../World/SGrid.h"
#include "../NetworkLayer/SAsteroidNetworkLayer.h"

SAstoroid::SAstoroid(uint32_t id, SPos& pos, SAstoroidType& atype, SAstoroidBelt* belt):
SObj(pos,0,0),STargetable(this), Processable(id){

	this->_oldPos = pos;
	_quan = myrandom(atype.getMminQuan(),atype.getMaxQuan());
	this->_type = &atype;
	this->_size = atype.getSize()* 100;
	this->_belt = belt;
}

void SAstoroid::Hit(SShot* shot, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y){
	pthread_mutex_lock(&this->lockUnit);
	if (shot->getDmgTypes() == DmgTypes::Mining && shot->getOwner()){
		if (shot->getOwner()->getCargoBay()){
			
			dmg = dmg / this->getAstoroidType()->getItemType()->getMass();
			dmg = dmg/1000;
			if (dmg > this->_quan){
				dmg = this->_quan;
			}
			this->_quan -= shot->getOwner()->getCargoBay()->AddReturn(this->getAstoroidType()->getItemType(),dmg);
		}
		this->_pos.grid->ReportHit(this,shot,ParticalTex::eks1,x,y);
	}
	pthread_mutex_unlock(&this->lockUnit);
}

bool SAstoroid::canBeRemoved(){
	if (this->_quan <= 0)
		return true;
	else
		return false;
}

void SAstoroid::announceRemovalOf(SObj* obj){

}

void SAstoroid::sendDepleted(SubscriptionLevel::Enum level){
	SendAstoroidDestroyd(_subscriptions[level], this, DestroyMode::Depleted);
}

void SAstoroid::sendFull(SubscriptionLevel::Enum level){
	SendAstoroidFull(_subscriptions[level], this);
}


SAstoroid::~SAstoroid() {
}

