/* 
 * File:   SUnitType.cpp
 * Author: karsten
 * 
 * Created on 11. februar 2014, 19:26
 */

#include "SUnitType.h"

SUnitType::SUnitType(uint32_t id){
	this->_id = id;
	this->_size = 1;
	this->_mass = 1;
	this->_cargo = 0;
	this->_hull = 0;
	this->_armor = 0;
	this->_energy = 0;
	this->_recharge = 0;
	this->_scanPRange = 0;
	this->_scanRange = 0;
	this->_topSpeed = 0;
	this->_agility = 0;
	this->_recoil = 10000;
	this->_recoilRecharge = 1000;
	for(int i = 0; i<6; i++)
		this->_shield[i] = 0;
	this->_deflector = 0;
}


SUnitType::~SUnitType() {
}

