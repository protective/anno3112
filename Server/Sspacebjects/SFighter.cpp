/* 
 * File:   SFighter.cpp
 * Author: karsten
 * 
 * Created on 25. januar 2014, 22:33
 */

#include "SFighter.h"


SFighter::SFighter(uint32_t id, SPos& pos, SFighterType& stype, uint32_t playerId):
SUnit(id,pos, stype, playerId){
}



SFighter::~SFighter() {
}

