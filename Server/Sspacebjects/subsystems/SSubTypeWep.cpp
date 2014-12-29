/* 
 * File:   SSubTypeWep.cpp
 * Author: karsten
 * 
 * Created on 30. juni 2011, 16:14
 */

#include "SSubTypeWep.h"



SSubTypeWep::SSubTypeWep() {
	this->_dmgMax = 0;
	this->_dmgMin = 0;
	this->_maxCd = 5000;
	this->_enegyCost = 0;
	this->_amoCost = 0;
	this->_maxAmo = 0;
	this->_amoCostType = NULL;
	this->_amoRechargeRate = 0;
	this->_texId = 1;
	this->_speed = 100;
	this->_hp = 0;
	this->_maxseq = 50;
	this->_dmgType = DmgTypes::normal;
	this->_range = 10;
	this->_resolution = 10;
	this->_spread = 10;
	this->_flightTime = 10;
	this->_tracking = 0;
	this->_trackingTime = 0;
	this->_recoil = 1000;
}

SSubTypeWep::~SSubTypeWep() {
}

