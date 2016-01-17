/* 
 * File:   SSubAble.cpp
 * Author: karsten
 * 
 * Created on 2. juli 2011, 12:29
 */

#include "SSubAble.h"
#include "../World/SGrid.h"
#include "SShip.h"
#include "subsystems/SSubSystemW.h"

#include "../NetworkLayer/SSubableNetworkLayer.h"
#include "SMetaObj.h"
#include "subsystems/SSubSystemTargetingI.h"

SSubAble::SSubAble(SObj* obj, uint32_t energy, uint32_t recharge, uint32_t scanRange, uint32_t scanPRange, uint32_t cargo) {
	this->_obj = obj;
	this->_cargoBay = new SCargoBay(this,cargo);
	this->_energy = energy*1000;
	this->_maxEnergy = energy*1000;
	this->_recharge = recharge* 1000;
	this->_scanRange = scanRange * 100;
	this->_scanPRange = scanPRange* 100;
	this->_recoil = 10000;
}


void SSubAble::updateTargetList(Processor* processor){
	//TODO fix
	
	map<uint32_t,SMetaObj*>& targets = this->obj()->getPos().grid->getMetaInGrid();
	
	_lockedTargets.clear();
	Destiny* destiny = this->obj()->getPos().grid->getDestiny();
	
	//destiny->inRange(this->obj(),11000000);

	for(map<uint32_t,SMetaObj*>::iterator it = targets.begin(); it!= targets.end();it++){
		if ((it->second->isAstoroid()) || (it->second->getTeam() != _obj->getTeam())){
			if(it->second->isTargetable()){
				SPos rpos;
				destiny->getPos(rpos,it->first);
				uint32_t range = Rangeobj(rpos, this->obj()->getPos());
				LockedTarget t(it->first, 0, range, 0, this->obj()->getPlayerId());
				_lockedTargets.insert(make_pair<LockedTarget,OBJID>(t,it->first)) ;
			}
		}
	}
}
OBJID SSubAble::getNextTarget(Processor* processor, SSlotNode* st){

	int32_t i= 0;
	if(!st->getSS() || !(st->getSS()->isWeapon() || st->getSS()->isFighter()))
		return 0;
	SSubSystemTargetingI* subsystem = st->getSS()->isWeapon();  
	list<TargetType::Enum> curTargetList;

	SOrdres* tempO = this->_obj->isUnit()->getOrdres();

	switch(subsystem->getTargetGroup()){
		case TargetGroup::Primary:{
			curTargetList = tempO->getPrimary();break;
		}case TargetGroup::Light:{
			curTargetList = tempO->getLight();break;
		}case TargetGroup::Medium:{
			curTargetList = tempO->getMedium();break;
		}case TargetGroup::Heavy:{
			curTargetList = tempO->getHeavy();break;
		}case TargetGroup::Special:{
			curTargetList = tempO->getSpecial();break;
		}
	}
	map<LockedTarget, OBJID>::iterator selTarget = _lockedTargets.end();
	Destiny* destiny = this->_obj->getPos().grid->getDestiny();
	for(list<TargetType::Enum>::iterator tt = curTargetList.begin(); tt!= curTargetList.end();tt++){

		if(selTarget != _lockedTargets.end())
			break;

		for(map<LockedTarget, OBJID>::iterator SO = _lockedTargets.begin(); SO != _lockedTargets.end();SO++){
			SMetaObj* meta =this->_obj->getPos().grid->getMetaInGrid(SO->second);
			if(!meta)
				continue;
			i++;
			if(subsystem->getTargetGroup() != TargetGroup::Primary && ((*tt) == meta->getTargetType() || ((*tt) == TargetType::All && meta->getTargetType() != TargetType::Astoroid))){
				SPos rpos;
				destiny->getPos(rpos, SO->second);
				if (1000*Rangeobj(this->obj()->getPos(),rpos) <= subsystem->getRange()){
					int32_t temp = Direction(_obj->getPos(),rpos)-(_obj->getPos().d/100) ;
					if(temp < 0) temp+=360;
					if(InAngle(temp,st->getST()->getFireDir())){ //found target break
						//subsys->setTarget(SO->first);
						selTarget = SO;
						break;
					}
				}
			}else if(subsystem->getTargetGroup() == TargetGroup::Primary && ( (*tt) == meta->getTargetType() || ((*tt) == TargetType::All && meta->getTargetType() != TargetType::Astoroid))){
				selTarget = SO;
				break;
			}
		}
	}
	if(selTarget == _lockedTargets.end()){
		return 0;
	}
	OBJID retval = selTarget->second;
	LockedTarget templ(selTarget->first);
	_lockedTargets.erase(selTarget);
	
	if(templ._pdestroyed < 3)
		templ._pdestroyed++;
	_lockedTargets.insert(make_pair<LockedTarget,OBJID>(templ, selTarget->second));
	return retval;
}


void SSubAble::updateTargetsPrio(Processor* processor){
	//TODO FIX
	
	if (!this->_obj->isUnit())
		return;
	if (!this->_obj->isUnit()->getOrdres())
		return;
	map<uint32_t, SMetaObj*> _cache;
	for(map<LockedTarget, OBJID>::iterator SO = this->_lockedTargets.begin(); SO != this->_lockedTargets.end();SO++){
		SMetaObj* tempMeta = this->_obj->getPos().grid->getMetaInGrid(SO->second);
		if(tempMeta){
			_cache[SO->second] = tempMeta;
		}
	}
	
	SOrdres* tempO = this->_obj->isUnit()->getOrdres();
	this->clearPrimeTarget();
	for(list<TargetType::Enum>::iterator tt = tempO->getPrimary().begin(); tt!= tempO->getPrimary().end();tt++){
		for(map<uint32_t, SMetaObj*>::iterator SO = _cache.begin(); SO != _cache.end();SO++){
			if((*tt) == SO->second->getTargetType() || ((*tt) == TargetType::All && SO->second->getTargetType() != TargetType::Astoroid)){
				setPrimeTarget(SO->first);
				break;
			}

		}
		if(this->getPrimeTarget())
			break;
	}
	Destiny* destiny = this->_obj->getPos().grid->getDestiny();
	for(SSlotNodeI it = slots.begin(); it != slots.end();it++){
		if(!it->second->getSS())
			continue;
		SSubSystemTargetingI* subsys = it->second->getSS()->isWeapon();
		if(!subsys)
			 subsys = it->second->getSS()->isFighter();
		if(!subsys)
			continue;
		
		uint32_t oldTarget = it->second->getSS()->getTarget();
		it->second->getSS()->setTarget(0);
		list<TargetType::Enum> curTargetList;

		switch(it->second->getSS()->getTargetGroup()){
			case TargetGroup::Primary:{
				curTargetList = tempO->getPrimary();break;
			}case TargetGroup::Light:{
				curTargetList = tempO->getLight();break;
			}case TargetGroup::Medium:{
				curTargetList = tempO->getMedium();break;
			}case TargetGroup::Heavy:{
				curTargetList = tempO->getHeavy();break;
			}case TargetGroup::Special:{
				curTargetList = tempO->getSpecial();break;
			}
		}
		for(list<TargetType::Enum>::iterator tt = curTargetList.begin(); tt!= curTargetList.end();tt++){
			for(map<uint32_t, SMetaObj*>::iterator SO = _cache.begin(); SO != _cache.end();SO++){
				if(subsys->getTargetGroup() != TargetGroup::Primary && ((*tt) == SO->second->getTargetType() || ((*tt) == TargetType::All && SO->second->getTargetType() != TargetType::Astoroid))){
					SPos rpos;
					destiny->getPos(rpos, SO->first);
					if (1000*Rangeobj(this->obj()->getPos(),rpos) <= subsys->getRange()){
						int32_t temp = Direction(_obj->getPos(),rpos)-(_obj->getPos().d/100) ;
						if(temp < 0) temp+=360;
						if(InAngle(temp,it->second->getST()->getFireDir())){ //found target break
							subsys->setTarget(SO->first);
							break;
						}
					}
				}else if(subsys->getTargetGroup() == TargetGroup::Primary && ( (*tt) == SO->second->getTargetType() || ((*tt) == TargetType::All && SO->second->getTargetType() != TargetType::Astoroid))){
					subsys->setTarget(SO->first);
					break;
				}
			}
			if(subsys->getTarget()) //we have a target break;
				break;
		}
		
		if(subsys->getTarget()){ //we have a target
			if(!oldTarget || subsys->getTarget() != oldTarget){ //reset lock if not the same as old target
				subsys->resetLockPower();
				if(!oldTarget) //we did not have a target before report new charge
					it->second->getSS()->reportCharge(SubscriptionLevel::details);

			}
		}
	}
}

void SSubAble::updateSubTarget(SSubSystem* subsys){
	if (subsys->canTarget()){
		subsys->setTarget(0);
		//for(STarI it = _primary.begin();it!= _primary.end();it++){
		//	subsys->setTarget(*it);
		//	break;
		//}
	}
}
uint32_t SSubAble::addRecoil(uint32_t recoil){
	uint32_t mr = getMaxRecoil();
	if (this->_recoil + recoil <= mr){
		this->_recoil += recoil;
		return recoil;
	}else{
		recoil = mr - this->_energy;
		this->_recoil = mr;
		return recoil;
	}
}
uint32_t SSubAble::getMaxRecoil(){
	if (obj()->isShip())
		obj()->isShip()->getShipType()->getRecoil();
	else 
		return 0;
}
uint32_t SSubAble::addEnergy(uint32_t energy){
	if (this->_energy + energy <= this->_maxEnergy){
		this->_energy+= energy;
		return energy;
	}else{
		energy = this->_maxEnergy- this->_energy;
		this->_energy = this->_maxEnergy;
		return energy;
	}
}


uint32_t SSubAble::useEnergy(uint32_t energy){
	if(this->_energy >= energy*1000){
		this->_energy -= energy*1000;
		return energy;
	}else{
		energy = floor(this->_energy/1000);
		this->_energy = this->_energy % 1000;
		return energy;
	}
}



SSubAble::~SSubAble() {
	for(SSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
		delete it->second->getSS();
	}

}

