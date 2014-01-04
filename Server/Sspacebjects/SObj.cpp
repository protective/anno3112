/* 
 * File:   GObj.cpp
 * Author: karsten
 * 
 * Created on 15. maj 2011, 21:23
 */

#include <stdint.h>

#include "SObj.h"

SObj::SObj(uint32_t id, SPos& pos, uint8_t team, uint32_t playerId) {
	this->_id = id;

	this->_team = team;
	this->_playerId = playerId;
	this->_pos.x = pos.x;
	this->_pos.y = pos.y;
	this->_pos.d = pos.d;
	this->_pos.grid = pos.grid;
	this->_pos.z = 0;
	this->_updateCounter = 0;
	this->_size = 120000;
	pthread_mutex_init(&this->lockUnit,NULL);
}

SPos& SObj::getPos(){
	return this->_pos;
}

SPos& SObj::getOldPos(){
	return this->_oldPos;
}

uint32_t SObj::getId(){
	return this->_id;
}

SpaceTypes::Enum SObj::getmyType(){
	return SpaceTypes::Invalid;
}

SObj::~SObj() {
}

