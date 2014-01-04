/* 
 * File:   GObj.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:23
 */

#include <stdint.h>

#include "CObj.h"

CObj::CObj(uint32_t id, uint32_t playerId, CPos& pos) {
	this->_id = id;
	this->_team = teamlist[playerId];
	this->_playerId = playerId;
	this->_pos.x = pos.x;
	this->_pos.y = pos.y;
	this->_pos.d = pos.d;
	this->_actualPos.x = pos.x;
	this->_actualPos.y = pos.y;
	this->_actualPos.d = pos.d;

	this->_lastUpdate = getTime();
	this->_procedTime = getTime();
	this->_fadetimer = 0;
	this->_maxfadetimer = 0;
}

CPos& CObj::getPos(){
	return this->_pos;
}

void CObj::ResivePosUpdate(CPos& pos){
	this->_pos.x = pos.x;
	this->_pos.y = pos.y;
	this->_pos.d = pos.d;
	this->_lastUpdate = getTime();
	this->_procedTime = getTime();
}



void CObj::Proces(uint32_t DTime){
	/*
	while(this->_procedTime<= getTime()){
		this->_procedTime += 1000/25;
		
		this->_pos.turn(100);
		//this->MovePos(VektorUnitX(this->_pos._d/100) * speed ,-(VektorUnitY(this->_pos._d/100)* speed));

	}
	//Move TDtime - procestime
	this->Move(getTime() - this->_lastUpdate);
	this->_lastUpdate = getTime();
	 * */
}



void CObj::MovePos(int32_t x, int32_t y){
	this->_pos.x+= x;
	this->_pos.y+= y;
}


CObj::~CObj() {
}

