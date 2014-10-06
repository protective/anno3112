/* 
 * File:   SAstoroidBelt.cpp
 * Author: karsten
 * 
 * Created on 12. april 2012, 20:49
 */

#include "SAstoroidBelt.h"
#include "../World/SWorld.h"
#include "../NetworkLayer/SAsteroidNetworkLayer.h"

SAstoroidBelt::SAstoroidBelt(uint32_t id, SPos& pos) :
SObj(id, pos,0,0), Processable(){
	_size = 1000;
}

void SAstoroidBelt::AddRoid(SAstoroidType* type, uint32_t counter){
	_roids.push_back(new SAstoroidBeltRoid(type,counter));
}

void SAstoroidBelt::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){

}

void SAstoroidBelt::proces(uint32_t delta, Processor* processor ){
	for(list<SAstoroidBeltRoid*>::iterator it = _roids.begin(); it != _roids.end(); it++){
		if((*it)->_roid == NULL && (*it)->_counter == 0 ){
			SPos temppos(myrandom(_pos.x-_size,_pos.x+_size),myrandom(_pos.y-_size,_pos.y+_size),0);
			temppos.grid = world->getGrids().begin()->second;
			(*it)->_roid = processor->createAsteroid(temppos, *(*it)->_type, this);
			//world->getGrids()[1]->addAstoroid((*it)->_roid);
		}else if((*it)->_roid == NULL && (*it)->_counter ){
			(*it)->_counter--;
		}
	}
}


SAstoroidBelt::~SAstoroidBelt() {
}

