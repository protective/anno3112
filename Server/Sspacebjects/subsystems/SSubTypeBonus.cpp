/* 
 * File:   SSubTypeBonus.cpp
 * Author: karsten
 * 
 * Created on 24. december 2011, 12:06
 */

#include "SSubTypeBonus.h"

SSubTypeBonus::SSubTypeBonus() {
}


void SSubTypeBonus::addBonus(BonusTypes::Enum bonus, int32_t value){
	_bonuslist[bonus] = value;
}


SSubTypeBonus::~SSubTypeBonus() {
}

