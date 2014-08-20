/* 
 * File:   GTargetable.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:32
 */

#include "STargetable.h"
#include "../NetworkLayer/STargetableNetworkLayer.h"

STargetable::STargetable(SObj* obj) {
	this->_obj =obj;
}

void STargetable::sendTargetHit(SubscriptionLevel::Enum level, uint32_t shot, ParticalTex::Enum tex, int32_t x, int32_t y){
	networkSendTargetHit(this->obj()->getSubscribers()[level], this, shot, tex, x, y);
}

STargetable::~STargetable() {
}

