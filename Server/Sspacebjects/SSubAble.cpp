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
	
	map<uint32_t,SMetaObj*>& targets = processor->getLocalMetas();
	
	
	for(map<uint32_t,SMetaObj*>::iterator it = targets.begin(); it!= targets.end();it++){
		if ((it->second->isAstoroid())||(it->second->getTeam() != _obj->getTeam())){
			if(it->second->isTargetable()){
				if (find(_lockedTargets.begin(),_lockedTargets.end(), it->first) == _lockedTargets.end()){
					_lockedTargets.push_back(it->first);
				}
			}
		}else{
			if(it->second->isTargetable()){
				_lockedTargets.remove(it->first);
			}
		}

	}

	list<TempSort> tempsort;
	for( list<uint32_t>::iterator it = _lockedTargets.begin(); it != _lockedTargets.end(); it++){
		
		if(*processor->getLocalMetas().find(*it) == *processor->getLocalMetas().end())
			continue;
		//TODO get prio
		//GET range
		uint32_t range = Rangeobj(*processor->getLocalMetas()[*it]->getPos(),this->obj()->getPos());
		tempsort.push_back(TempSort(*it,0,range,this->obj()->getPlayerId()));
	}
	tempsort.sort();
	_lockedTargets.clear();
	for( list<TempSort>::iterator it = tempsort.begin(); it != tempsort.end(); it++){
		_lockedTargets.push_back((*it)._target);
	}
	
}

void SSubAble::updateTargetsPrio(Processor* processor){
	//TODO FIX
	
	if (!this->_obj->isUnit())
		return;
	if (!this->_obj->isUnit()->getOrdres())
		return;
	map<uint32_t, SMetaObj*> _cache;
	for(list<uint32_t>::iterator SO = this->_lockedTargets.begin(); SO != this->_lockedTargets.end();SO++){
		SMetaObj* tempMeta = processor->getMeta(*SO);
		if(tempMeta){
			_cache[*SO] = tempMeta;
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
					if (1000*Rangeobj(this->obj()->getPos(),*SO->second->getPos()) <= subsys->getRange()){
						int32_t temp = Direction(_obj->getPos(),*SO->second->getPos())-(_obj->getPos().d/100) ;
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

