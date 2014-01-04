/* 
 * File:   AUnitControle.cpp
 * Author: karsten
 * 
 * Created on 29. juni 2012, 16:37
 */

#include <stdint.h>

#include "AUnitControle.h"
#include "spaceobjects/subsystems/CSubType.h"
#include "spaceobjects/subsystems/CSubTypeFac.h"
#include "spaceobjects/subsystems/CSubSystemFac.h"
#include "../Ordre/AOrdreBuild.h"
#include "../Ordre/AOrdreMine.h"
#include "../ABeacon.h"
#include "spaceobjects/subsystems/CLoadout.h"
AUnitControle::AUnitControle() {
	_shiptypePower[1] = 650;
	_shiptypePower[6] = 100;
	_shiptypePower[16] = 200;
	_shiptypePower[42] = 200;
	_shiptypePower[43] = 900;
	_shiptypePower[46] = 40;
	
}

AChoice* AUnitControle::getRandomChoice(uint32_t unit){
	
	//int32_t i = myrandom(0,_choices[unit].size()-1);
	if(_choices[unit].size() > 0){
		list<AChoice*>::iterator it = _choices[unit].begin();
		while (it != _choices[unit].end()){
			if (myrandom(1,10) <= 2){
				return *it;
			}else
				it++;
		}
		return *_choices[unit].begin();
	}else
		return NULL;
}

void AUnitControle::updateKeyUnits(){
	
	for(map<uint32_t,CShip*>::iterator it = _choiceUnits.begin() ; it != _choiceUnits.end() ; it++){//all the units we need to check
		for( list<AChoice*>::iterator it2 = _choices[it->first].begin() ; it2 != _choices[it->first].end(); it2++){
			delete *it2;
		}
		_choices[it->first].clear();
	}
	
	for(map<uint32_t, AUnitTimeValue>::iterator it = _miningUnits.begin() ; it != _miningUnits.end() ;){
		if(playerObj->getObjs().find(it->first) == playerObj->getObjs().end()){
			_miningUnits.erase(it++);
		}else
			it++;
	}
	
	_choiceUnits.clear();
	_productionUnits.clear();
	for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin() ; it != playerObj->getObjs().end() ; it++){
		if(it->second->getPlayerId() == playerId){
			if (it->second->isShip() && it->second->isShip()->getShipType()->getId() == 19) { // 19 = station TODO fix HardCode
				_choiceUnits[it->first] = it->second->isShip();
				_productionUnits[it->first] = it->second->isShip();
				playerObj->ServerNotisSubscribe(*it->second); //get an update of the status
				playerObj->ServerNotisUnSubscribe(*it->second);
			} 

			if (it->second->isShip() && it->second->isShip()->getShipType()->getId() == 26) { // 26 = freighter TODO fix HardCode
				_choiceUnits[it->first] = it->second->isShip();
				playerObj->ServerNotisSubscribe(*it->second); //get an update of the status
				playerObj->ServerNotisUnSubscribe(*it->second);
			}
			if(it->second->isShip() && _shipsFits[it->first] == false){
				playerObj->ServerNotisSubscribe(*it->second); //get an update of the status
				playerObj->ServerNotisUnSubscribe(*it->second);
			}
		}
	}
	

}

bool compare_coice (AChoice* first, AChoice* second)
{
	if(first->_economic > second->_economic)
		return true;
	return false;
}

CShip*AUnitControle::getClosestProductionUnit(){
	CShip* temp = NULL;
	uint32_t trange = 0;
	for(map<uint32_t, CShip*>::iterator it = _productionUnits.begin(); it!= _productionUnits.end();it++){
		uint32_t t2range;
		if(temp == NULL || trange < (t2range = Rangeobj(temp->getPos(),it->second->getPos()))){
			trange = t2range;
			temp = it->second;
		}
	}
	return temp;
}

void AUnitControle::UpdatePosibleChoises(map<uint32_t, ABeacon*>& beacons){	
	updateKeyUnits();
	_missingMaterials.clear();
	_missingMaterialsCount.clear();
	cerr<<"economic "<<_economic<<" power "<<_power<<endl;
	if((_economic < 0.4 && _totalEconomic < 3000)||(_economic < 0.6 && _totalEconomic < 2000) || _totalEconomic < 1000){

		_missingMaterials[26] += 10;
		_missingMaterialsCount[26] = 1;
	}
	if(_power < 0.7){
		_missingMaterials[6] += 0.9 - ((float)max((uint32_t)1,getShipCount(playerId,shipTypes[6]))*0.1);
		_missingMaterialsCount[6] = 1;
		_missingMaterials[16] += 0.6/max((uint32_t)1,getShipCount(playerId,shipTypes[16]));
		_missingMaterialsCount[16] = 1;
		_missingMaterials[1] += 0.5/max((uint32_t)1,getShipCount(playerId,shipTypes[1]));
		_missingMaterialsCount[1] = 1;
		_missingMaterials[46] += 0.6/max((uint32_t)1,getShipCount(playerId,shipTypes[46]));
		_missingMaterialsCount[46] = 1;
	}
	//clean the ship fits
	for(map<uint32_t, bool>::iterator it = _shipsFits.begin() ; it != _shipsFits.end();){
		if(playerObj->getObjs().find(it->first) == playerObj->getObjs().end())
			_shipsFits.erase(it++);
		else
			it++;
	}
	
	
	for(map<uint32_t,CShip*>::iterator it = _productionUnits.begin(); it != _productionUnits.end(); it++){//all the units we need to check
		if(playerObj->getObjs().find(it->first) != playerObj->getObjs().end()){ //Check if unit still exist;
			if(playerObj->getObjs()[it->first]->issubable()){
				CCargoBay* cargo = playerObj->getObjs()[it->first]->issubable()->getCargoBay();
				for(map<CItemType*, uint32_t>::iterator it2 =  cargo->getContent().begin(); it2 != cargo->getContent().end();it2++){
					_missingMaterialsCount[it2->first->getTypeID()] = 0 - it2->second;
				}
			}
		}
	}
	
	//handle building items to ships missing fits //TODO need to be updated when client fits is implemented
	for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin() ; it != playerObj->getObjs().end() ; it++){
		if(it->second->getPlayerId() == playerId){
			if(_shipsFits.find(it->first) == _shipsFits.end())
				_shipsFits[it->first] = false;
			
			if (_shipsFits[it->first] == false && it->second->isShip()){

				bool sus = false;
				if(it->second->isShip()->getShipType()->getId() == 26){//freighter
					for(map<uint32_t, CSlotNode*>::iterator it2 = it->second->isShip()->getSlots().begin(); it2 != it->second->isShip()->getSlots().end();it2++) {
						if(it2->second->getST()->slotType() == 18){//mining slot
							if( !it2->second->getSS()||(it2->second->getSS() && it2->second->getSS()->Xitem() < 4)){
								
								for(map<uint32_t,CObj*>::iterator it3 = playerObj->getObjs().begin() ; it3 != playerObj->getObjs().end() ; it3++){
									if (it3->second->getPlayerId() == playerId && Rangeobj(it3->second->getPos(),it->second->getPos()) < 1000 && it3->second->issubable() && it3->second->issubable()->getCargoBay()->GetReturn(itemlist[5],1) > 0){
										playerObj->ServerRequsetFit(it2->second,it3->second->issubable()->getCargoBay(),itemlist[5],4);
										break;
									}
								}
								_missingMaterials[5] += 20;
								_missingMaterialsCount[5] += 4;
								cerr<<"missing mining"<<endl;
								
								sus = true;
							} 
						}
					}
				}else {
					if(globalLoadout.find(it->second->isShip()->getShipType()->getId()) != globalLoadout.end()){
						CLoadout* loadout = globalLoadout[it->second->isShip()->getShipType()->getId()];
						for(map<uint32_t, singleload>::iterator it2 = loadout->getItems().begin(); it2 != loadout->getItems().end();it2++){
							if( !it->second->isShip()->getSlots()[it2->first]->getSS()||(it->second->isShip()->getSlots()[it2->first]->getSS() && it->second->isShip()->getSlots()[it2->first]->getSS()->Xitem() < it2->second._xitem)){
								//atemt to fit one
								for(map<uint32_t,CObj*>::iterator it3 = playerObj->getObjs().begin() ; it3 != playerObj->getObjs().end() ; it3++){
									if (it3->second->getPlayerId() == playerId && Rangeobj(it3->second->getPos(),it->second->getPos()) < 1000 && it3->second->issubable() && it3->second->issubable()->getCargoBay()->GetReturn(it2->second._type,1) > 0){
										playerObj->ServerRequsetFit(it->second->isShip()->getSlots()[it2->first],it3->second->issubable()->getCargoBay(),it2->second._type,1);
										playerObj->ServerRequestChangeSubTG(it->second->issubable(),it2->first,it2->second._targetGroup);
										break;
									}
								}
								uint32_t build= 0;
								if(it->second->isShip()->getSlots()[it2->first]->getSS())
									build = it2->second._xitem -it->second->isShip()->getSlots()[it2->first]->getSS()->Xitem();
								else
									build = it2->second._xitem;

								
								_missingMaterialsCount[it2->second._type->getTypeID()] += build;
								if(_missingMaterialsCount[it2->second._type->getTypeID()] > 0)
									_missingMaterials[it2->second._type->getTypeID()] += 2;
								sus = true;
							}
						}
					}
				}
				if(sus == false){
					_shipsFits[it->first] = true;
					if(it->second->isShip()->getShipType()->getId() == 26){//freighter
						for(map<uint32_t,CSlotNode*>::iterator it2 = it->second->issubable()->getSlots().begin(); it2 != it->second->issubable()->getSlots().end();it2++){
							if(it2->second->getSS() && it2->second->getST()->slotType() == 18){
								playerObj->ServerRequestChangeSubTG(it->second->issubable(), it2->second->getId(),TargetGroup::Special);
							}
						}
						playerObj->ServerRequestChangeOrdre(it->second,globalOrders[2]); //set to mining

					}
				}
			}
		}
	}
	float count = 0;
	for (map<uint32_t,float>::iterator it =  _missingMaterials.begin(); it != _missingMaterials.end();it++){
		count += it->second;

	}
	for (map<uint32_t,float>::iterator it =  _missingMaterials.begin(); it != _missingMaterials.end();it++){
		_missingMaterials[it->first] /= count; 

	}	
	

	//production
	for(map<uint32_t,CShip*>::iterator it = _productionUnits.begin(); it != _productionUnits.end(); it++){//all the units we need to check
		if(playerObj->getObjs().find(it->first) != playerObj->getObjs().end()){ //Check if unit still exist;
			for (map<uint32_t, CSlotNode*>::iterator it2 = it->second->getSlots().begin(); it2 != it->second->getSlots().end(); it2++){
				if (it2->second->getSS()){
					if (it2->second->getSS()->isFac() &&  it2->second->getSS()->isFac()->cooldown(0) == -1){
						cerr<<"run building "<<endl;
						CSubTypeFac* factype = it2->second->getSS()->isFac()->getItemType()->getSubType()->isFac();
						
						for (map<uint32_t, CItemType*>::iterator it3 =  factype->getCanBuildList().begin(); it3 != factype->getCanBuildList().end();it3++){
								uint32_t buildingCount = 0;
								AChoice* tchoise = new AChoice(0,0,0,NULL,NULL);
								buildingCount+=min((int32_t)8,_missingMaterialsCount[it3->first]);
								
								AOrdre* tordre = new AOrdreBuild(it2->second->getSS()->isFac(),it3->second,min((int32_t)8,_missingMaterialsCount[it3->first]));
								tchoise->SetOrdre(tordre);
								tchoise->_economic = _missingMaterials[it3->first] * 1000;
								
								_choices[it->first].push_back(tchoise);
								if(_missingMaterials[it3->first] > 0 && !it2->second->getSS()->isFac()->haveEnoughTobuild(it3->second)){
									for(map<uint32_t,bmaterial>::iterator it4 = it3->second->getCost().begin(); it4 != it3->second->getCost().end(); it4++){
										if(it4->second._quan > it2->second->getOwner()->getCargoBay()->GetReturn(it4->second._item,0-1))
											_missingMaterials[it4->first] += 1 * _missingMaterials[it3->first];
									}
								}else{
								
									if(buildingCount > 0 && buildingCount < 5){
										float tempmiss = 0;
										uint32_t tempfound = 0;
										for (map<uint32_t, CItemType*>::iterator it4 =  factype->getCanBuildList().begin(); it4 != factype->getCanBuildList().end();it4++){
											if (tempmiss < _missingMaterials[it4->first] && it3->first != it4->first){
													tempmiss = _missingMaterials[it4->first];
													tempfound = it4->first;
											}
										}
										if(tempfound > 0){
											((AOrdreBuild*)tordre)->build(itemlist[tempfound],min((int32_t)8,_missingMaterialsCount[tempfound]));
											//_missingMaterialsCount[tempfound] = 0;
											//tchoise->_economic += _missingMaterials[tempfound] * 1000;

										}
									}					
								}
							}
						}
					}
				}	
			}
			count = 0;
			for (map<uint32_t,float>::iterator it2 =  _missingMaterials.begin(); it2 != _missingMaterials.end();it2++){
				if(it2->first == 24 || it2->first == 34 || it2->first == 29 || it2->first == 27 || it2->first == 31)
					count += it2->second;
			}
			for (map<uint32_t,float>::iterator it2 =  _missingMaterials.begin(); it2 != _missingMaterials.end();it2++){
				_missingMaterials[it2->first] /= count; 
				//cerr<<itemlist[it2->first]->getName()<<">> "<<it2->second<<" <<"<<endl;
			}	
			for (map<uint32_t,float>::iterator it2 =  _missingMaterials.begin(); it2 != _missingMaterials.end();it2++){
				if(it2->first == 24 || it2->first == 34 || it2->first == 29 || it2->first == 27 || it2->first == 31)
					cerr<<"missing mineral "<<itemlist[it2->first]->getName()<<" "<<_missingMaterials[it2->first]<<endl;
			}
			_choices[it->first].sort(compare_coice);
		}
	
	
		//mining
	CSubAble* mainproductionunit = NULL;
	for(map<uint32_t,CShip*>::iterator it = _productionUnits.begin(); it != _productionUnits.end(); it++){//all the units we need to check
		mainproductionunit = it->second;
	}
	for(map<uint32_t,CShip*>::iterator it = _choiceUnits.begin(); it != _choiceUnits.end(); it++){//all the units we need to check
		if(playerObj->getObjs().find(it->first) != playerObj->getObjs().end()){ //Check if unit still exist;
			if(it->second->isShip()->getShipType()->getId() == 26 && _shipsFits[it->first] == true){//freighter ready to go
				if(_miningUnits[it->first]._value != it->second->getCargoBay()->getcurCargo()){
					_miningUnits[it->first]._time = getTime();
					_miningUnits[it->first]._value = it->second->getCargoBay()->getcurCargo();
				}
				if(_miningUnits[it->first]._time +30000 < getTime() && (it->second->getCargoBay()->getcurCargo() <  it->second->getCargoBay()->getmaxCargo() * 0.95 || it->second->isMovable()->getSpeed() == 0)){
					_miningUnits[it->first]._time = getTime();
					_miningUnits[it->first]._value = it->second->getCargoBay()->getcurCargo();
					list<ABeacon*> bcs = findMiningBeacon(beacons);
					for(list<ABeacon*>::iterator it2 = bcs.begin(); it2 != bcs.end(); it2++){
						float missingMod = 0;
						for(map<uint32_t,float>::iterator it3 = (*it2)->getResourses().begin(); it3 != (*it2)->getResourses().end(); it3++){
							missingMod += _missingMaterials[it3->first] * it3->second;
						}
						if(missingMod){
							AChoice* tchoise = new AChoice(0,100,((pow(((float)1/missingMod),2)))*-(int32_t)(((float) sqrt(Rangeobj((*it2)->getGroup()->getPos(),mainproductionunit->obj()->getPos())/10))),NULL,(*it2));
							AOrdreMine* tordre = new AOrdreMine(it->second,mainproductionunit,&((*it2)->getGroup()->getPos()));
							tchoise->SetOrdre(tordre);
							_choices[it->first].push_back(tchoise);
						}
					}
				}		
			}
		}
		_choices[it->first].sort(compare_coice);
	}
}

list<ABeacon*> AUnitControle::findMiningBeacon(map<uint32_t, ABeacon*>& beacons){
	
	list<ABeacon*> temp;
	for(map<uint32_t, ABeacon*>::iterator it = beacons.begin() ; it != beacons.end(); it++){
		if( it->second->getTotalTactical() > 50){
			temp.push_back(it->second);
		}
	}
	return temp;
}

AUnitControle::~AUnitControle() {
}

