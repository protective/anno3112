/* 
 * File:   AObjGroup.cpp
 * Author: karsten
 * 
 * Created on 6. juni 2012, 23:11
 */

#include "AObjGroup.h"
#include "../../Client/spaceobjects/CShip.h"
#include "UnitControle/AUnitControle.h"
AObjGroup::AObjGroup() {
	_pos.d = 0;
	_pos.x = 0;
	_pos.y = 0;
	_power = 0;
	_tactical = 0;
	_thread = 0;
	_hostileCount = 0;
	_frindlyCount = 0;
	_pos.grid = NULL;
	_beacon = NULL;
	this->recompute();
}

AObjGroup* AObjGroup::splitGroup(){
	AObjGroup* group = new AObjGroup();
	group->setBeacon(_beacon);
	while (group->getPower() < getPower()){
		group->addUnit(this->getobjs().begin()->second);
		this->removeUnit(this->getobjs().begin()->second);
	}
	return group;
}

void AObjGroup::subSplitGroup(AObjGroup* g1, AObjGroup* g2){

	map<uint32_t,CObj*>::iterator it  = this->getobjs().begin();
	while (it != this->getobjs().end()){
		
		if(g1->getPower() < g2->getPower()){
			g1->addUnit(it->second);
			g1->recompute();
		}else{
			g2->addUnit(it->second);
			g2->recompute();
		}
		it++;
	}
	g1->setBeacon(_beacon);
	g2->setBeacon(_beacon);
}

void AObjGroup::recompute(){
	_power = 0;
	_tactical = 0;
	_thread = 0;
	_hostileCount = 0;
	_frindlyCount = 0;
	for(map<uint32_t,CObj*>::iterator it = _objs.begin(); it != _objs.end(); it++){
		if (it->second->isShip() && it->second->isShip()->getShipType()->getId() != 26){
			if (it->second->getTeam() != teamlist[playerId]){
				_thread += unitControle->getShipTypePower()[it->second->isShip()->getShipType()->getId()];
				_hostileCount += 1;
			}else{
				_frindlyCount += 1;
				_power += unitControle->getShipTypePower()[it->second->isShip()->getShipType()->getId()]; //TODO implement power to ships
			}
		}else if(it->second->isAstoroid()){
			_tactical += 100; //TODO implement power to ships
			_thread += 0;
		}
	}
	
	CShip* closesProductionUnit = unitControle->getClosestProductionUnit();
	if(closesProductionUnit){
		uint32_t rangemod = ceil((float)Rangeobj(_pos,closesProductionUnit->getPos())/10000);
		//_thread *= rangemod;
	}


	int32_t tx = 0;
	int32_t ty = 0;
	for(map<uint32_t,CObj*>::iterator it = _objs.begin(); it != _objs.end(); it++){
		tx += it->second->getPos().x;
		ty += it->second->getPos().y;
	}
	//cerr<<"tx "<<tx<<" ty "<<ty<<" "<<playerMultiSels.size()<<endl;
	tx = (double)tx / _objs.size();
	ty = (double)ty / _objs.size();
	_pos.x = tx;
	_pos.y = ty;
}

void AObjGroup::removeUnit(CObj* obj){ //TODO fix not computing whole time
	_objs.erase(obj->getId());
	//this->recompute();
}

void AObjGroup::addUnit(CObj* obj){ //TODO fix not computing whole time
	_objs[obj->getId()] = obj;
	//this->recompute();
}

AObjGroup::~AObjGroup() {
}

