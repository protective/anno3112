/* 
 * File:   GShip.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:34
 */

#include "SShip.h"


SShip::SShip(uint32_t id, SPos& pos, SShipType& stype, uint32_t playerId) :
SUnit(id,pos, stype, playerId){
	_sType = &stype;
}


void SShip::proces(uint32_t delta, Processor* processor){
	postProces(delta);
	if(_lastCombat < 1000000)
		_lastCombat++;
	
	if(this->_updateCounter)
		this->_updateCounter--;
	for(SSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
		if (it->second->getSS())
			it->second->getSS()->proces(processor);
	}
	if(_order){
		if(_targetUpdateCounter % 5 == 0){
			_order->proces(OrdreEvent::Tick5,this);
		}
		if(_targetUpdateCounter % 10 == 0){
			_order->proces(OrdreEvent::Tick10,this);
		}
		if(_targetUpdateCounter % 25 == 0){
			_order->proces(OrdreEvent::Tick25,this);
		}
	}
	_targetUpdateCounter++;
	this->addRecoil(getUnitType()->getRecoilRecharge());
	if (_targetUpdateCounter % 5 == 0){
		this->updateTargetsPrio(_processor);
		this->addEnergy(_recharge/5);
	}
	if (_targetUpdateCounter % 25 == 0){
		updateTargetList(_processor);
		this->updateAutoMove();
		sendPosUpdate(SubscriptionLevel::lowFreq);

		
		this->_bonuslist.clear();
		for(SSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
			if (it->second->getSS()){
				if (it->second->getSS()->isBonus()){
					it->second->getSS()->isBonus()->procesBonus(this);
				}
			}

		}
		this->_recharge = getUnitType()->getRecharge() * 1000;
		this->_maxEnergy = getUnitType()->getEnergy() * 1000;
		this->_maxdeflector = getUnitType()->getDeflector()*1000;
		//this->_deflector = stype.getDeflector()*1000;
		for (int i = 0; i< 6; i++){
			this->_maxshield[i] = getUnitType()->getShield(i) * getUnitType()->getShieldStr() * 10;
		}
		this->_maxarmor = getUnitType()->getArmor()*1000;
		this->_maxhull = getUnitType()->getHull()*1000;

		this->_scanRange = getUnitType()->getScanRange() * 100;
		this->_scanPRange = getUnitType()->getScanPRange() * 100;
		_topSpeed = getUnitType()->getTopSpeed() * 100;
		_agility = getUnitType()->getAgility();
		for (map<BonusTypes::Enum, int32_t>::iterator it = this->_bonuslist.begin(); it != this->_bonuslist.end();it++){
			switch(it->first){
				case BonusTypes::Armor:{this->_maxarmor+= it->second;break;}
				case BonusTypes::Deflector:{this->_maxdeflector+= it->second;break;}
				case BonusTypes::Hull:{this->_maxhull+= it->second;break;}
				case BonusTypes::ShieldStr:{
					for(uint32_t i = 0; i < 6 ; i++){
						this->_maxshield[i] += (this->getUnitType()->getShield(i) * it->second)/100;
					}
					break;
				}
				case BonusTypes::ERecharge:{this->_recharge+= it->second;break;}
				case BonusTypes::Energy:{this->_maxEnergy+= it->second;break;}
				case BonusTypes::ScanRange:{this->_scanRange+= (it->second/10);break;}
				case BonusTypes::ScanPRange:{this->_scanPRange+= (it->second/10);break;}
				case BonusTypes::SpeedThruster:{this->_topSpeed+= (it->second/(getUnitType()->getMass()/10));break;}
				case BonusTypes::ManuvereThruster:{this->_agility+= (it->second/(getUnitType()->getMass()*10));break;}			
			}
		}
		for(SSlotNodeI it = this->slots.begin(); it != this->slots.end(); it++){
			if (it->second->getSS())
				it->second->getSS()->reset();
		}
		//cerr<<"this->_topSpeed"<<this->_topSpeed<<endl;
	}
	if (_targetUpdateCounter == 100)
		_targetUpdateCounter = 0;

}


SShip::~SShip() {


}

