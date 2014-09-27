/* 
 * File:   SUnit.cpp
 * Author: karsten
 * 
 * Created on 11. februar 2014, 19:25
 */

#include "SUnit.h"
#include "SShip.h"
#include "SFighter.h"
#include "SProgrammable.h"
#include "../World/SGrid.h"
#include "../NetworkLayer/SShipNetworkLayer.h"
#include "../Commands/CommandRemove.h"
#include "../Commands/CommandEnterGrid.h"
#include "../Commands/CommandExitGrid.h"
#include "../Commands/CommandHit.h"
#include "SMetaObj.h"

SUnit::SUnit(uint32_t id, SPos& pos, SUnitType& stype, uint32_t playerId):
SObj(id, pos,teamlist[playerId],playerId),SSubAble(this,stype.getEnergy(),stype.getRecharge(),stype.getScanRange(),stype.getScanPRange(),stype.getCargo()),STargetable(this),SMovable(this, stype.getTopSpeed(), stype.getAgility()), Processable() , SProgrammable(id) {
	this->_autoMoveCounter = 0;
	this->_autoMovePoint = 0;
	this->_targetPos.x = pos.x;
	this->_targetPos.y = pos.y;
	this->_targetPos.d = pos.d;
	this->_size = stype.getSize()*100;
	for (map<uint32_t, SShipTypeSlotData*>::iterator it = stype.getSlots().begin(); it != stype.getSlots().end(); it++){
		this->slots[it->first] = new SSlotNode(this,it->first, it->second);
		if(it->second->getBaseItem())
			this->AddSub(it->second->getBaseItem(),it->first,it->second->getBaseItemCount());
	}
	this->_maxdeflector = stype.getDeflector()*1000;
	this->_deflector = stype.getDeflector()*1000;
	for (int i = 0; i< 6; i++){
		this->_maxshield[i] = stype.getShield(i) * stype.getShieldStr() * 10;
		this->_shield[i] = this->_maxshield[i];
	}
	this->_maxarmor = stype.getArmor()*1000;
	this->_maxhull = stype.getHull()*1000;
	this->_armor = stype.getArmor()*1000;
	this->_hull = stype.getHull()*1000;
	this->_order = globalOrders[playerId][0];
	_lastCombat = 0;
}
void SUnit::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	cerr<<"subscribe unit clid ="<<clientId<<endl;
	if(this->isShip())
		this->isShip()->sendFull(clientId);
	_subscriptions[level].push_back(clientId);
}

void SUnit::proces(uint32_t delta, Processor* processor){
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
		if(_id == 2)
			setProgram(_processor->getPrograms()["test"]);
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


void SUnit::postProces(uint32_t delta){
	
	Move(delta);

	/*
	for (list<uint8_t>::iterator it = allteams.begin(); it != allteams.end(); it++){
		bool found = false;
		for (SObjI so = this->getPos().grid->getObjInGrid().begin(); so != this->getPos().grid->getObjInGrid().end();so++){
			if (so->second->isShip() && so->second->getTeam() == (*it)){
				//we are invisible
				if (Rangeobj(so->second->getPos(),this->getPos()) < so->second->isUnit()->getScanRange()/100){
					found = true;
					//TODO SUBSCR
					if(_visibleTo.find(so->second->getTeam()) == _visibleTo.end() || _visibleTo[so->second->getTeam()] == Visibility::Invisible){
						_visibleTo[*it] = Visibility::PreVisible;
					}
					
					break;
				}			
			}
		}
		if(!found){
			//TODO SUBSCR
			/*
			if(_visibleTo.find(*it) != _visibleTo.end() && _visibleTo[*it] == Visibility::Visible){
				_visibleTo[*it] = Visibility::PreInvisible;
			}
			 * 
		}
	}
	if(this->_order){
		for(map<uint32_t, SObj*>::iterator it = this->getPos().grid->getObjInGrid().begin(); it != this->getPos().grid->getObjInGrid().end();it++){
			if(this != it->second && (it->second->isShip()) || it->second->isAstoroid()){
				uint32_t a = Rangeobj(this->_pos, it->second->getPos());
				uint32_t b = Rangeobj(this->_oldPos, it->second->getOldPos());
				_order->procesRangeChange(this,it->second, a*100,b*100);
			}
		}
	}

	*/
}

void SUnit::updateAutoMove(){

	_MovementStatus = 0;
	if(this->_order){
		
		switch(this->_order->getPrimeOrdre()){
			case OrdresTactice::Front:{
				if(_rangeToTargetPos <= 10){
					if (this->_primeTarget){	
						//this->setTargetPos(_targetPos.x,_targetPos.y,100* Direction(this->_pos,this->_primeTarget->obj()->getPos()));
					}else{
						this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));
					}
				}else{
					this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));
				}
				break;
			}
			/*
			case OrdresTactice::FrontMinRange:{
				
				if (this->_primeTarget){
					uint32_t rangeToPrime = Rangeobj(_pos,this->_primeTarget->obj()->getPos());
					cerr<<"rangeto "<<rangeToPrime<<endl;
					if (rangeToPrime * 100 > _order->getAutoMoveRange()){
						this->setTargetPos(_primeTarget->obj()->getPos().x,_primeTarget->obj()->getPos().y,100* Direction(this->_pos,this->_primeTarget->obj()->getPos()));
				
					}else{
						this->setTargetPos(_pos.x,_pos.y,100* Direction(this->_pos,this->_primeTarget->obj()->getPos()));
					}
					_MovementStatus |= MoveBitF::TargetPosLock;
				}else{
					this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));
				}
				
				break;
			}
			case OrdresTactice::FrontMaxRange:{
				
				if (this->_primeTarget){
					uint32_t rangeToPrime = Rangeobj(_pos,this->_primeTarget->obj()->getPos());
					cerr<<"rangeto "<<rangeToPrime<<endl;
					if (rangeToPrime * 100 < _order->getAutoMoveRange()){
						uint32_t a = Direction(this->_pos,this->_primeTarget->obj()->getPos());
						uint32_t b = a + 180;
						if(b >= 360)
							b = b - 360;
						this->setTargetPos(_pos.x + (VektorUnitX(b)*30000), _pos.y + (VektorUnitY(b)*30000),100 * b);
						_MovementStatus |= MoveBitF::TargetPosLock;
					}else{
						this->setTargetPos(_targetPos.x,_targetPos.y,100* Direction(this->_pos,this->_primeTarget->obj()->getPos()));
					}
					
				}else{
					this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));
				}
				
				break;
			}
			*/
			case OrdresTactice::Evasive:{
					
				_autoMoveCounter++;
				if(_rangeToTargetPos <= 100 || _autoMoveCounter > 30){
					_autoMovePoint = 0;
				}
				if(_autoMoveCounter > 30)
					_autoMoveCounter = 0;

				if(_autoMovePoint == 0){
					
					_autoMovePoint = myrandom(1,8);
				}
				if(!this->_processor)
					return;
				SMetaObj* metaPrime = this->_processor->getMeta(this->_primeTarget);
				
				if (metaPrime){
					SPos metaPrimePos; metaPrimePos = metaPrime->getRPos();
					_MovementStatus |= MoveBitF::TargetPosLock;
					int32_t tarx;
					int32_t tary;
					switch(_autoMovePoint){
						case 1:{
							tarx = metaPrimePos.x + _order->getAutoMoveRange();
							tary = metaPrimePos.y + _order->getAutoMoveRange();
							break;
						}
						case 2:{
							tarx = metaPrimePos.x - _order->getAutoMoveRange();
							tary = metaPrimePos.y + _order->getAutoMoveRange();
							break;
						}
						case 3:{
							tarx = metaPrimePos.x + _order->getAutoMoveRange();
							tary = metaPrimePos.y - _order->getAutoMoveRange();
							break;
						}
						case 4:{
							tarx = metaPrimePos.x - _order->getAutoMoveRange();
							tary = metaPrimePos.y - _order->getAutoMoveRange();
							break;
						}
						case 5:{
							tarx = metaPrimePos.x;
							tary = metaPrimePos.y + _order->getAutoMoveRange();
							break;
						}
						case 6:{
							tarx = metaPrimePos.x;
							tary = metaPrimePos.y - _order->getAutoMoveRange();
							break;
						}
						case 7:{
							tarx = metaPrimePos.x + _order->getAutoMoveRange();
							tary = metaPrimePos.y;
							break;
						}
						case 8:{
							tarx = metaPrimePos.x - _order->getAutoMoveRange();
							tary = metaPrimePos.y;
							break;
						}
					}

					this->setTargetPos(tarx,tary,(100 * Deg(tarx-this->_pos.x,tary-this->_pos.y)));

				}
				break;
			}
			
			case OrdresTactice::No_move:{
				this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));

			}
			default:{
				this->setTargetPos(_targetPos.x,_targetPos.y,(100 * Deg(this->_targetPos.x-this->_pos.x,this->_targetPos.y-this->_pos.y)));

				break;
			}
		}
	}
}



void SUnit::Move(uint32_t deltaT){
	_rangeToTargetPos = Rangeobj(this->getPos(),this->getTargetPos()) ;

	this->_oldPos = this->_pos;
	int32_t targetDir = 0;
	
	targetDir = this->_targetPos.d;
	
	int32_t b;
	int32_t a; //amount to turn
	double acc = (double)_agility;
	double turnVal;
	//speed up or down
	if(acc > 0){
		if (_rangeToTargetPos < _topSpeed/acc)
			_maxSpeed = _rangeToTargetPos * 100;
	}else
		_maxSpeed = 0;

	if(_rangeToTargetPos > 20){
		if(_speed < _maxSpeed)
			_speed += acc*2;
	}else if (_rangeToTargetPos > 10){
		if (_maxSpeed / 100 > _rangeToTargetPos )
			_maxSpeed = (_rangeToTargetPos+ 10)* 100;
	}else{
		_maxSpeed = 0;
	}
	
	if(_speed > _maxSpeed){
		_speed -= acc;
		if(_speed < 0)
			_speed = 0;
		if(_speed < _maxSpeed)
			_speed = _maxSpeed;
	}

	//calk diff to turn
	if (targetDir >= this->_pos.d)
		b = targetDir - this->_pos.d;
	else
		b = targetDir + 36000 - this->_pos.d;

	//calk amount to turn
	if (b <= 18000)
		a = b;
	else if( b > 18000)
		a = 36000 - b;

	//reduce maxspeed if the turn is sharp
	if(a < 300 * 0.95)
		_maxSpeed = _topSpeed;
	else
		_maxSpeed= _topSpeed * (1 - ((double)a / 8000));
		
	//turnval reduces by the speed
	if(_speed > 0){
		if(_speed < _topSpeed * 0.75)
			turnVal = 300 * (1 - ((double)_speed / (double)_topSpeed));
		else
			turnVal = 300 * 0.25;
	}else
		turnVal = 300;

	turnVal = turnVal * (((double)_agility / 100) / 2);
	
	if (a < turnVal)
		turnVal = a;
	if (b > 18000)
		this->_pos.turn((int32_t)-turnVal);
	else
		this->_pos.turn((int32_t)turnVal);
	
	this->MovePos((VektorUnitX(this->_pos.d/100) * _speed)/100 ,-((VektorUnitY(this->_pos.d/100)* _speed)/100));

}

void SUnit::MovePos(int32_t x, int32_t y){
	this->_pos.x+= x;
	this->_pos.y+= y;
}

void SUnit::setTargetPos(SPos& pos){
	cerr<<"set target pos x"<<pos.x<<" y "<<pos.y<<" d "<<pos.d<<endl;
	this->_targetPos.x = pos.x;
	this->_targetPos.y = pos.y;
	this->_targetPos.d = pos.d;
	this->_updateCounter = 0;
	this->sendPosUpdate(SubscriptionLevel::lowFreq);
}

void SUnit::setTargetPos(int32_t x, int32_t y, int32_t d){
	if(this->getPos().grid
		&& (int32_t)0 - ((int32_t)this->getPos().grid->getWight()/2) < x
		&& (int32_t)0 - ((int32_t)this->getPos().grid->getHight()/2) < y
		&& x < (int32_t)this->getPos().grid->getWight()/2
		&& y < (int32_t)this->getPos().grid->getHight()/2 )
		{
			this->_targetPos.x = x;
			this->_targetPos.y = y;
			this->_targetPos.d = d;
			this->_updateCounter = 0;
		}
}
void SUnit::setTargetPos(int32_t x, int32_t y){
	this->setTargetPos(x, y, _targetPos.d);
}

uint32_t SUnit::FitAddSub(SItemType* type, uint32_t slot, uint32_t Xitem, SCargoBay* cargobay){
	return cargobay->RemoveReturn(type ,this->AddSub(type,slot,cargobay->GetReturn(type,Xitem)));
}

uint32_t SUnit::FitRemoveSub(uint32_t slot, uint32_t Xitem, SCargoBay* cargobay){
	if(this->getSlots()[slot]->getSS() && Xitem > 0){
		SItemType * titem = this->getSlots()[slot]->getSS()->getItemType();

		return cargobay->AddReturn(titem,this->RemoveSub(slot,Xitem));
	}
	return 0;
}



uint32_t SUnit::AddSub(SItemType* type, uint32_t slot, uint32_t Xitem){
	
	if (this->slots[slot] && Xitem > 0){
		if(this->slots[slot]->getSS()){
			if(this->slots[slot]->getSS()->getItemType()->getTypeID() != type->getTypeID() ){
				return 0;
			}
		}else{
			if(this->slots[slot]->CanFit(type->getSubType()->getMountType(),this->slots[slot]->getST()->slotType())){
				if(type->getSubType()->getClass() == SubSystemClass::Wep){
					SSubSystem* temp = new SSubSystemW(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
					
				}else if(type->getSubType()->getClass() == SubSystemClass::Fighter){
					SSubSystem* temp = new SSubSystemFighter(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
					
				}else if(type->getSubType()->getClass() == SubSystemClass::Fac){
					SSubSystem* temp = new SSubSystemFac(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
					
				}else if(type->getSubType()->getClass() == SubSystemClass::Ref){
					SSubSystem* temp = new SSubSystemRef(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
					
				}else if(type->getSubType()->getClass() == SubSystemClass::bonus){
					SSubSystem* temp = new SSubSystemBonus(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
					
				}else if(type->getSubType()->getClass() == SubSystemClass::boost){
					SSubSystem* temp = new SSubSystemBoost(*((SObj*)this),*this->slots[slot],slot,type,Xitem);
					if(temp->Xitem()){
						this->slots[slot]->setSS(temp);
						this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
					}else{
						delete temp;
						return 0;
					}
					return this->slots[slot]->getSS()->Xitem();
				}
			}else
				return 0;
		}
		if (this->slots[slot]->getSS()){
			uint32_t t = this->slots[slot]->getSS()->AddItem(Xitem);
			this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
			return t;
		}else{
			cerr<<"WARNING Ship::ADDSub no subsystem created"<<endl;
			return 0;
		}
	}
	cerr<<"WARNING Ship::ADDSub slot not found"<<endl;
	return 0;

}

uint32_t SUnit::RemoveSub(uint32_t slot, uint32_t Xitem){
	if (this->slots[slot]->getSS()){

		uint32_t t = this->slots[slot]->getSS()->RemoveItem(Xitem);
		this->slots[slot]->getSS()->reportCharge(SubscriptionLevel::lowFreq);
		if (this->slots[slot]->getSS()->Xitem() == 0){
			delete this->slots[slot]->getSS();
			this->slots[slot]->setSS(NULL);
		}

		return t;
	}
	return 0;
}

void SUnit::hit(uint32_t shot, uint32_t dmg, DmgTypes::Enum dmgtype, Shields::Enum impact, int32_t x, int32_t y){
	pthread_mutex_lock(&this->lockUnit);
	_lastCombat = 0;
	ParticalTex::Enum tex = ParticalTex::eks1;
	if(dmgtype == DmgTypes::normal){
		bool firsthitfound = false;
		
		if (_shield[impact] > 0 && !_shieldDown[impact]){
			if (dmg <= 2000)
				tex= ParticalTex::eksshc1;
			else if(dmg <= 3000)
				tex= ParticalTex::eksshc2;
			else if(dmg <= 4000)
				tex= ParticalTex::eksshc3;
			else if(dmg <= 5000)
				tex= ParticalTex::eksshc4;
			else if(dmg <= 6000)
				tex= ParticalTex::eksshc4l;
			else if(dmg <= 7000)
				tex= ParticalTex::eksshc5;
			else if(dmg <= 8000)
				tex= ParticalTex::eksshc5l;
			else if(dmg <= 9000)
				tex= ParticalTex::eksshc6;
			else if(dmg <= 10000)
				tex= ParticalTex::eksshc6l;
			else if(dmg <= 11000)
				tex= ParticalTex::eksshc7;
			else if(dmg > 11000)
				tex= ParticalTex::eksshc7l;
			firsthitfound = true;
			if(dmg <= _shield[impact] ){
				_shield[impact] -= dmg;
				dmg = 0;
			}else{
				dmg -= _shield[impact];
				_shield[impact] =0;
			}
		}
		if(_deflector > 0 && !_deflectorDown && dmg > 0){

			if(!firsthitfound){
				if (dmg <= 2000)
					tex= ParticalTex::eksshc1;
				else if(dmg <= 3000)
					tex= ParticalTex::eksshc2;
				else if(dmg <= 4000)
					tex= ParticalTex::eksshc3;
				else if(dmg <= 5000)
					tex= ParticalTex::eksshc4;
				else if(dmg <= 6000)
					tex= ParticalTex::eksshc4l;
				else if(dmg <= 7000)
					tex= ParticalTex::eksshc5;
				else if(dmg <= 8000)
					tex= ParticalTex::eksshc5l;
				else if(dmg <= 9000)
					tex= ParticalTex::eksshc6;
				else if(dmg <= 10000)
					tex= ParticalTex::eksshc6l;
				else if(dmg <= 11000)
					tex= ParticalTex::eksshc7;
				else if(dmg > 11000)
					tex= ParticalTex::eksshc7l;
			}
			firsthitfound = true;
			if(dmg <= _deflector){
				_deflector -= dmg;
				dmg = 0;
			}else{
				dmg -= _deflector;
				_deflector = 0;
			}
		}
		if(_armor > 0 && dmg > 0){

			if(!firsthitfound){
				if (dmg <= 2000)
					tex= ParticalTex::eks1;
				else if(dmg <= 3000)
					tex= ParticalTex::eks2;
				else if(dmg <= 4000)
					tex= ParticalTex::eks3;
				else if(dmg <= 5000)
					tex= ParticalTex::eks4;
				else if(dmg <= 6000)
					tex= ParticalTex::eks4l;
				else if(dmg <= 7000)
					tex= ParticalTex::eks5;
				else if(dmg <= 8000)
					tex= ParticalTex::eks5l;
				else if(dmg <= 9000)
					tex= ParticalTex::eks6;
				else if(dmg <= 10000)
					tex= ParticalTex::eks6l;
				else if(dmg <= 11000)
					tex= ParticalTex::eks7l;
				else if(dmg > 11000)
					tex= ParticalTex::eks7l;
			}

			firsthitfound = true;
			if(dmg <= _armor){
				_armor -= dmg;
				dmg = 0;
			}else{
				dmg -= _armor;
				_armor = 0;
			}
		}
		if(_hull > 0 && dmg > 0){

			if(!firsthitfound){
				if (dmg <= 2000)
					tex= ParticalTex::eks1;
				else if(dmg <= 3000)
					tex= ParticalTex::eks2;
				else if(dmg <= 4000)
					tex= ParticalTex::eks3;
				else if(dmg <= 5000)
					tex= ParticalTex::eks4;
				else if(dmg <= 6000)
					tex= ParticalTex::eks4l;
				else if(dmg <= 7000)
					tex= ParticalTex::eks5;
				else if(dmg <= 8000)
					tex= ParticalTex::eks5l;
				else if(dmg <= 9000)
					tex= ParticalTex::eks6;
				else if(dmg <= 10000)
					tex= ParticalTex::eks6l;
				else if(dmg <= 11000)
					tex= ParticalTex::eks7l;
				else if(dmg > 11000)
					tex= ParticalTex::eks7l;
			}
			firsthitfound = true;
			if(dmg <= _hull){
				_hull -= dmg;
				dmg = 0;
			}else{
				dmg -= _hull;
				_hull = 0;
				cerr<<"ship dead !!!!!!!!!!!!!"<<endl;
				sendRemoved(SubscriptionLevel::lowFreq, DestroyMode::Destroy);
				
				this->addCommand(new CommandExitGrid(0,this->_pos.grid->getId(),_id));
				this->_pos.grid = NULL;
				this->addCommand(new CommandRemove(0,this));
			}
		}
	}
	
	//TODO fix report hit
	sendTargetHit(SubscriptionLevel::lowFreq, shot, tex, x, y);
	sendHpUdate(SubscriptionLevel::lowFreq);
	//this->_pos.grid->ReportHit(this,shot,tex,x,y);

	pthread_mutex_unlock(&this->lockUnit);
	
}

void SUnit::sendHpUdate(SubscriptionLevel::Enum level){
	networkSendUnitHpUdate(this->getSubscribers()[level], this);
}

bool SUnit::canBeRemoved(){
	if (this->_hull <= 0)
		return true;
	else
		return false;
}

void SUnit::sendPosUpdate(SubscriptionLevel::Enum level){
	sendUnitPosUpdate(_subscriptions[level],this);
}

void SUnit::sendFull(uint32_t client){
	list<uint32_t> temp;
	temp.push_back(client);
	sendUnitFull(temp,this);
}
void SUnit::sendFull(SubscriptionLevel::Enum level){
	sendUnitFull(_subscriptions[level],this);
}

void SUnit::sendRemoved(SubscriptionLevel::Enum level, DestroyMode::Enum mode){
	sendUnitRemoved(_subscriptions[level],this, mode);
}



SUnit::~SUnit() {
}

