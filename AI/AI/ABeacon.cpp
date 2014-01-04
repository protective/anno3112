/* 
 * File:   ABeacon.cpp
 * Author: karsten
 * 
 * Created on 6. juni 2012, 23:02
 */

#include "ABeacon.h"
#include "spaceobjects/CTargetable.h"
#include "spaceobjects/CAstoroid.h"

ABeacon::ABeacon(AObjGroup* group) {
	_group = group;
	_threatValue = 0;
	_powerValue = 0;
	_tacticalValue = 0;
	_economicValue = 0;
	_sumpowerValue = 0;
	_sumtacticalValue = 0;
	_sumthreatValue = 0;
	_sumeconomicValue = 0;
}

void ABeacon::proces(){

}


void ABeacon::update(){
	_tacticalValue = _group->getTactical();
	_powerValue = _group->getPower();
	_threatValue = _group->getThread();
	
	_resourses[24] = 0;
	_resourses[34] = 0;
	_resourses[29] = 0;
	_resourses[27] = 0;
	_resourses[31] = 0;
	uint32_t ascounter = 0;
	for(map<uint32_t, CObj*>::iterator it = _group->getobjs().begin(); it != _group->getobjs().end(); it++){
		if(it->second->isAstoroid()){
			ascounter += 1;
			if(it->second->isAstoroid()->getAstoroidType()->getId() == 8){
				_resourses[24] += 1;
			}
			if(it->second->isAstoroid()->getAstoroidType()->getId() == 37){
				_resourses[34] += 1;
				_resourses[29] += 0.1;
			}
			if(it->second->isAstoroid()->getAstoroidType()->getId() == 36){
				_resourses[29] += 1;
				_resourses[27] += 0.5;
			}
			if(it->second->isAstoroid()->getAstoroidType()->getId() == 35){
				_resourses[29] += 1;
				_resourses[27] += 1;
			}
			if(it->second->isAstoroid()->getAstoroidType()->getId() == 38){
				_resourses[31] += 1;
			}
		}
	}
	_resourses[24] /= ascounter;
	_resourses[34] /= ascounter;
	_resourses[29] /= ascounter;
	_resourses[27] /= ascounter;
	_resourses[31] /= ascounter;
	
}

ABeacon::~ABeacon() {
}

