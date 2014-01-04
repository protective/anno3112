/* 
 * File:   AIMain.cpp
 * Author: karsten
 * 
 * Created on 5. juni 2012, 23:31
 */

#include <stdint.h>

#include "AIMain.h"
#include "spaceobjects/CObj.h"
#include "Ordre/AOrdreChangeOrdre.h"
#include "spaceobjects/CPos.h"
#include "spaceobjects/CShip.h"
#include "Ordre/AOrdreSet.h"
#include "Ordre/AOrdreMove.h"
#include "AChoice.h"

AIMain::AIMain() {
	_curgroup = 0;
}

int32_t AIMain::CalculateUtility(){
	int32_t utility= 0;
	for (map<uint32_t , ABeacon*>::iterator it2 = _beacons.begin(); it2 != _beacons.end(); it2++){
		
		float a = 0;
		if(it2->second->getTotalThread() > 0){
			a = (float)it2->second->getTotalPower()/it2->second->getTotalThread();
		}
		//cerr<<"a "<<a<<endl;
		float mod = 0;
		float combatmod = 0;
		if (a > 1.5){
			combatmod = 2 * a;
		}else if( a > 1){
			combatmod = 0.4;
		}else if( a > 0.8){
			combatmod = -200;
		}else if( a > 0){
			combatmod = -200;
		}else if( a == 0){
			combatmod = 1;
		}
		mod /=1000;
		
		if(it2->second->getTotalPower() > 0 && it2->second->getTotalTactical() > 400){
			utility += it2->second->getTotalTactical();
		}
		
		utility += (float)it2->second->getTotalPower()*combatmod; //+ ((float)it2->second->getTotalTactical()*mod)+
		if(it2->second->getTotalThread() == 0)
			utility += (float)it2->second->getTotalEconomic();
		// 

	}
	return utility;
}

void AIMain::findsolution(){
	
	AOrdreSet* oldOrdreSet = NULL;
	for (uint32_t run = 0; run < 30000; run++){
		int32_t Curentmax = 0;
		ABeacon* curentBeacon = NULL;
		AOrdreSet* ordreset = new AOrdreSet();
		for(map<uint32_t , AObjGroup*>::iterator it = _combatGroup.begin() ; it != _combatGroup.end(); it++){
			//cerr<<"proces combat group> size"<<it->second->getobjs().size()<<endl;	
			
			int32_t i = myrandom(0,10);
			if(i < 0){//DO one beacon
				
				curentBeacon = this->findRandomBeacon(it->second);
				ABeacon* oneBeacon = curentBeacon;
				if(oneBeacon){
				
					ordreset->addordreDelete(new AOrdreMove(it->second,oneBeacon->getGroup()->getPos()));
					
					int32_t movecost = (Rangeobj(it->second->getPos(), oneBeacon->getGroup()->getPos())/1000)*it->second->getFriendlyCount();
					ordreset->addMoveCost(movecost);
					oneBeacon->addsum(it->second->getPower(),0,0,0);
					it->second->getBeacon()->removesum(it->second->getPower(),0,0,0);
				}
			}else{//DO two beacons
				AObjGroup* g1 = new AObjGroup();
				AObjGroup* g2 = new AObjGroup();
				it->second->subSplitGroup(g1,g2);
				g1->recompute();
				g2->recompute();
				//cerr<<"g1 s>"<<g1->getobjs().size()<<" g2 s>"<<g2->getobjs().size()<<endl;
				ABeacon* twoBeacon1 = this->findRandomBeacon(g1);
	
				ABeacon* twoBeacon2 = this->findRandomBeacon(g2);

			
				if(twoBeacon1 && twoBeacon2){

					//cerr<<"two beacon "<<twoBeacon1<<" "<<twoBeacon2<<endl;
					
					if(twoBeacon1->getGroup()->getHostileCount()){
						ordreset->addordreDelete(new AOrdreChangeOrdre(g1,3));
						
					}else
						ordreset->addordreDelete(new AOrdreChangeOrdre(g1,0));
						ordreset->addordreDelete(new AOrdreMove(g1,twoBeacon1->getGroup()->getPos()));
					
					if(twoBeacon2->getGroup()->getHostileCount()){
						ordreset->addordreDelete(new AOrdreChangeOrdre(g2,3));
						
					}else
						ordreset->addordreDelete(new AOrdreChangeOrdre(g2,0));
						ordreset->addordreDelete(new AOrdreMove(g2,twoBeacon2->getGroup()->getPos()));
					
					int32_t movecost;
					movecost = (Rangeobj(it->second->getPos(), twoBeacon1->getGroup()->getPos())/100)*g1->getFriendlyCount();
					ordreset->addMoveCost(movecost);
					
					int32_t dirToBeacon;
					dirToBeacon = 100 * Deg(twoBeacon1->getGroup()->getPos().x-it->second->getPos().x,twoBeacon1->getGroup()->getPos().y-it->second->getPos().y);
					for(map<uint32_t , ABeacon*>::iterator it2 = _beacons.begin(); it2 != _beacons.end(); it2++){
						if (it2->second->getGroup()->getHostileCount() > 0 && Rangeobj(it2->second->getGroup()->getPos(),twoBeacon1->getGroup()->getPos()) < 2000000){
							int32_t dirToHostileBeacon = 100 * Deg(it2->second->getGroup()->getPos().x-it->second->getPos().x,it2->second->getGroup()->getPos().y-it->second->getPos().y);
							double mod = (double)1-( ((double)dirDiff(dirToBeacon,dirToHostileBeacon))/18000);
							it2->second->addsum((double)g1->getPower()*mod,0,0,0);
							//cerr<<"added power "<<g1->getPower()<<" mod "<<mod<<endl;
						}
					}

					
					movecost = (Rangeobj(it->second->getPos(), twoBeacon2->getGroup()->getPos())/100)*g2->getFriendlyCount();
					ordreset->addMoveCost(movecost);
	
					dirToBeacon = 100 * Deg(twoBeacon2->getGroup()->getPos().x-it->second->getPos().x,twoBeacon2->getGroup()->getPos().y-it->second->getPos().y);
					for(map<uint32_t , ABeacon*>::iterator it2 = _beacons.begin(); it2 != _beacons.end(); it2++){
						if (it2->second->getGroup()->getHostileCount() > 0 && Rangeobj(it2->second->getGroup()->getPos(),twoBeacon2->getGroup()->getPos()) < 2000000){
							int32_t dirToHostileBeacon = 100 * Deg(it2->second->getGroup()->getPos().x-it->second->getPos().x,it2->second->getGroup()->getPos().y-it->second->getPos().y);
							double mod = (double)1-( ((double)dirDiff(dirToBeacon,dirToHostileBeacon))/18000);
							it2->second->addsum((double)g2->getPower()*mod,0,0,0);
							//cerr<<"added power "<<g2->getPower()<<" mod "<<mod<<endl;
						}
					}					
					twoBeacon1->addsum(0.5*g1->getPower(),0,0,0);
					twoBeacon2->addsum(0.5*g2->getPower(),0,0,0);
					it->second->getBeacon()->removesum(it->second->getPower(),0,0,0);
					


				}
				ordreset->addtoDelete(g1);
				ordreset->addtoDelete(g2);
			}
		}
		
		for(map<uint32_t,CShip*>::iterator it = unitControle->getChoiceUnits().begin() ; it != unitControle->getChoiceUnits().end();it++){
			AChoice* choice = NULL;
			choice = unitControle->getRandomChoice(it->first);
			if (_unitBeacon[it->first] && choice){
				if(choice->_affectedBeacon)
					choice->_affectedBeacon->addsum(choice->_power,0,choice->_tactical,choice->_economic);
				else
					_unitBeacon[it->first]->addsum(choice->_power,0,choice->_tactical,choice->_economic);
				ordreset->addordre(choice->_ordre);
			}
		}
		
		int32_t myt = this->CalculateUtility();
		ordreset->setUtility(myt);
		for(map<uint32_t , ABeacon*>::iterator it = _beacons.begin() ; it != _beacons.end(); it++){
			it->second->resetsum();
		
		}
		
		if(ordreset && oldOrdreSet){
	
			if(ordreset->gettotalUtil() > oldOrdreSet->gettotalUtil()){
				delete oldOrdreSet;
				oldOrdreSet = ordreset;
			}else{
				delete ordreset;
			}
		}else{
			oldOrdreSet = ordreset;
		}
	
	}
	//TODO find close optimal first
	if(oldOrdreSet){
		oldOrdreSet->execute();
		cerr<<"exe"<<endl;
		delete oldOrdreSet;
	}
}
	
ABeacon* AIMain::findRandomBeacon(AObjGroup* group){
	int32_t i = myrandom(0,10);
	if(i < 1)
		return this->findrandomCombatBeacon(group);
	else if(i < 5)
		return this->findrandomAllBeacon(group);
	else if(i < 11)
		return this->findownBeacon(group);
}
ABeacon* AIMain::findownBeacon(AObjGroup* group){
	//*retcurmax = this->CalculateUtility() ;

	return group->getBeacon();
}


ABeacon* AIMain::findrandomAllBeacon(AObjGroup* group){
	list<ABeacon*> combatbeacons;
	for(map<uint32_t , ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		if(it->second->getTotalTactical() > 0 || it->second->getGroup()->getHostileCount() > 0)
			combatbeacons.push_back(it->second);
	}
	
	int32_t i = myrandom(0,combatbeacons.size()-1);
	list<ABeacon*>::iterator it = combatbeacons.begin();
	int32_t j = 0;
	while (j < i){
		it++;
		j++;
	}
	
	return *it;
}


ABeacon* AIMain::findrandomCombatBeacon(AObjGroup* group){
	list<ABeacon*> combatbeacons;
	for(map<uint32_t , ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		if (it->second->getGroup()->getHostileCount() > 0){
			combatbeacons.push_back(it->second);
		}
	}
	if(combatbeacons.size()== 0)
		return NULL;
	int32_t i = myrandom(0,combatbeacons.size()-1);
	list<ABeacon*>::iterator it = combatbeacons.begin();
	int32_t j = 0;
	while (j < i){
		it++;
		j++;
	}
	
	return *it;
}

void AIMain::recreateGroups(){
	for(map<uint32_t, AObjGroup*>::iterator it = _groups.begin(); it != _groups.end(); it++){
		delete it->second;
	}
	
	for(map<uint32_t, ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		delete it->second;
	}
	
	_unitBeacon.clear();
	
	_combatGroup.clear();
	_groups.clear();
	_beacons.clear();
	_curgroup = 0;
	map<uint32_t, bool> marked;
	
	CObj* lastUnit = NULL;
	uint32_t epselon = 200;
	bool ungroupunit = true;
	while (ungroupunit){
		_curgroup++;
		ungroupunit = false;
		list<CObj*> toExplore;
		for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin() ; it != playerObj->getObjs().end() ; it++){
			if(it->second and !it->second->isShot()){
				if(!marked[it->first]){
					toExplore.push_back(it->second);
					break;
				}
			}
		}
		while(toExplore.size() > 0){
			CObj* lastunit = toExplore.back();
			toExplore.pop_back();
			for(map<uint32_t,CObj*>::iterator it2 = playerObj->getObjs().begin(); it2 != playerObj->getObjs().end(); it2++){
				if(it2->second and !it2->second->isShot()){
					if(!marked[it2->first]){
						uint32_t temprange = 0;
						if (it2->second->isShip()){
							if(lastunit->isShip())
								temprange = Rangeobj(it2->second->isMovable()->getTargetPos(), lastunit->isMovable()->getTargetPos());
							else
								temprange = Rangeobj(it2->second->isMovable()->getTargetPos(), lastunit->getPos());
						}else{
							temprange = Rangeobj(it2->second->getPos(), lastunit->getPos());
						}
						if(it2->second && temprange <= epselon){
							if(!_groups[_curgroup]){
								_groups[_curgroup] = new AObjGroup();
								_beacons[_curgroup] = new ABeacon(_groups[_curgroup]);
								_groups[_curgroup]->setBeacon(_beacons[_curgroup]);
							}
							_groups[_curgroup]->addUnit(it2->second);
							_unitBeacon[it2->first] = _beacons[_curgroup];
							marked[it2->first] = true;
							toExplore.push_back(it2->second);
						}else{ // unit do not match in group
							ungroupunit = true;
						}
					}
				}
			}
		}
	}
	
	for(map<uint32_t, AObjGroup*>::iterator it = _groups.begin(); it != _groups.end(); it++){
		it->second->recompute();
	}
	cerr<<"done groups"<<endl;
	
	for(map<uint32_t , AObjGroup*>::iterator it = _groups.begin() ; it != _groups.end(); it++){
		for (map<uint32_t, CObj*>::iterator it2 = it->second->getobjs().begin(); it2 != it->second->getobjs().end(); it2++){
			if (it2->second->isShip()){
				if(it2->second->isShip()->getPlayerId() == playerId && unitControle->getShipFit()[it2->first] == true){
					if ( it2->second->isShip()->getShipType()->getId() != 26){
						if(_combatGroup.find(it->first) == _combatGroup.end()){
							_combatGroup[it->first] = new AObjGroup();
							_combatGroup[it->first]->setBeacon(it->second->getBeacon());
						}
						_combatGroup[it->first]->addUnit(it2->second);
					}	
				}
			}
		}
	}
	for(map<uint32_t, AObjGroup*>::iterator it = _combatGroup.begin(); it != _combatGroup.end(); it++){
		it->second->recompute();
	}
	
	for (map<uint32_t, ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		it->second->update();
		//cerr<<"beacon*********************"<<endl;
		//cerr<<"thread "<<it->second->getGroup()->getThread()<<endl;
		//cerr<<"power "<<it->second->getGroup()->getPower()<<endl;
		//cerr<<"tactical "<<it->second->getGroup()->getTactical()<<endl;
	}
	
	//update beacons with thread from other close beacons
	map<uint32_t, uint32_t> beacontoAdd;
	for (map<uint32_t, ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		for (map<uint32_t, ABeacon*>::iterator it2 = _beacons.begin(); it2 != _beacons.end(); it2++){
			if(Rangeobj(it->second->getGroup()->getPos(), it2->second->getGroup()->getPos()) < 200000 && it->first != it2->first){
				beacontoAdd[it->first] = it->second->getTotalThread();
			}
		}
	}
	for (map<uint32_t, ABeacon*>::iterator it = _beacons.begin(); it != _beacons.end(); it++){
		it->second->add(0,beacontoAdd[it->first],0,0);
	}
	//calculate build focus
	uint32_t totalPower = 0;
	uint32_t combatPower = 0;
	uint32_t echonomicPower = 0;
	for(map<uint32_t,CObj*>::iterator it = playerObj->getObjs().begin() ; it != playerObj->getObjs().end() ; it++){
		if(it->second->isShip() && it->second->getPlayerId() == playerId){
			if (it->second->isShip()->getShipType()->getId() == 26){
				totalPower+= 100;
				echonomicPower += 100;
			}else if(it->second->isShip()->getShipType()->getId() == 6){
				totalPower+= 100;
				combatPower += 100;
			}else if(it->second->isShip()->getShipType()->getId() == 16){
				totalPower+= 150;
				combatPower += 150;
			}else if(it->second->isShip()->getShipType()->getId() == 1){
				totalPower+= 850;
				combatPower += 850;
			}
		}
	}
	
	unitControle->SetUnitFocus((float)combatPower/totalPower,combatPower,(float)echonomicPower/totalPower,echonomicPower);
	unitControle->UpdatePosibleChoises(_beacons);
	this->findsolution();
}
	

AIMain::~AIMain() {
}

