/* 
 * File:   SAstoroid.cpp
 * Author: karsten
 * 
 * Created on 5. oktober 2011, 20:39
 */

#include "SAstoroid.h"
#include "SShot.h"
#include "../World/SGrid.h"
#include "../Commands/CommandEnterGrid.h"
#include "../Commands/CommandExitGrid.h"
#include "../Commands/CargoCommands/CommandCargoAdd.h"
#include "../NetworkLayer/SAsteroidNetworkLayer.h"

SAstoroid::SAstoroid(uint32_t id, SPos& pos, SAstoroidType& atype, SAstoroidBelt* belt):
SObj(id, pos,0,0),STargetable(this), Processable(){

	this->_oldPos = pos;
	_quan = myrandom(atype.getMminQuan(),atype.getMaxQuan());
	this->_type = &atype;
	this->_size = atype.getSize()* 100;
	this->_belt = belt;
	
	this->addCommand(new CommandEnterGrid(0,pos.grid->getId(),id));

}


void SAstoroid::hit(uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y){
	if (dmgtype== DmgTypes::Mining && owner){

		dmg = dmg / this->getAstoroidType()->getItemType()->getMass();
		dmg = dmg/1000;
		if (dmg > this->_quan){
			dmg = this->_quan;
		}

		this->_quan -= dmg;
		CommandCargoAdd* cmd = new CommandCargoAdd(owner,this->getAstoroidType()->getItemTypeId(), dmg);
		if (networkControl->addCommandToProcesable(cmd,owner))
			delete cmd;
		sendTargetHit(SubscriptionLevel::lowFreq, shot, ParticalTex::eks1, x, y);
	
		if(this->_quan == 0){
		
			sendDepleted(SubscriptionLevel::lowFreq);

			this->addCommand(new CommandExitGrid(0,this->_pos.grid->getId(),_id));
			this->_pos.grid = NULL;
			this->addCommand(new CommandRemove(0,this));

		
		}
		
		
	}
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

void SAstoroid::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	if(this->isAstoroid())
		this->isAstoroid()->sendFull(clientId);
	_subscriptions[level].push_back(clientId);
}

void SAstoroid::sendFull(uint32_t client){
	list<uint32_t> temp;
	temp.push_back(client);
	SendAstoroidFull(temp,this);
}

void SAstoroid::sendFull(SubscriptionLevel::Enum level){
	SendAstoroidFull(_subscriptions[level], this);
}


SAstoroid::~SAstoroid() {
}

