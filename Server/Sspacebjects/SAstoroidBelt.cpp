/* 
 * File:   SAstoroidBelt.cpp
 * Author: karsten
 * 
 * Created on 12. april 2012, 20:49
 */

#include "SAstoroidBelt.h"
#include "../World/SWorld.h"
SAstoroidBelt::SAstoroidBelt(uint32_t id, SPos& pos) :
SObj(id,pos,0,0){
	_size = 1000;
}

void SAstoroidBelt::AddRoid(SAstoroidType* type, uint32_t counter){
	_roids.push_back(new SAstoroidBeltRoid(type,counter));
}

void SAstoroidBelt::proces(){
	for(list<SAstoroidBeltRoid*>::iterator it = _roids.begin(); it != _roids.end(); it++){
		if((*it)->_roid == NULL && (*it)->_counter == 0 ){
			SPos temppos(myrandom(_pos.x-_size,_pos.x+_size),myrandom(_pos.y-_size,_pos.y+_size),0);
			temppos.grid = world->getGrids()[1];
			(*it)->_roid = new SAstoroid(getFreeID(), temppos, *(*it)->_type, this);
			world->getGrids()[1]->addAstoroid((*it)->_roid);
		}else if((*it)->_roid == NULL && (*it)->_counter ){
			(*it)->_counter--;
		}
	}
}

void SAstoroidBelt::announceRemovalOf(SObj* obj){
	if(obj->isAstoroid()){
		for(list<SAstoroidBeltRoid*>::iterator it = _roids.begin(); it != _roids.end(); it++){
			if((*it)->_roid == obj->isAstoroid()){
				(*it)->_roid = NULL;
				(*it)->_counter = (*it)->_maxcounter;
			}
		}
	}
}

SAstoroidBelt::~SAstoroidBelt() {
}

