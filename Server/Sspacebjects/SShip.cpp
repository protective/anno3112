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
	SUnit::proces(delta,processor);


}

void SShip::subscribeClient(uint32_t clientId, SubscriptionLevel::Enum level){
	cerr<<"subscribe ship clid ="<<clientId<<endl;
	this->sendFull(clientId);
	_subscriptions[level].push_back(clientId);
}

SShip::~SShip() {


}

