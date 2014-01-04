/* 
 * File:   CSubTypeBoost.cpp
 * Author: karsten
 * 
 * Created on 25. december 2011, 18:46
 */

#include "CSubTypeBoost.h"

CSubTypeBoost::CSubTypeBoost() {
	this->_maxCd = 5000;
	this->_enegyCost = 0;
	this->_amoCost = 0;
	this->_maxAmo = 0;
	this->_amoCostType = NULL;
	this->_amoRechargeRate = 0;

}

CSubTypeBoost::CSubTypeBoost(BonusTypes::Enum boostType, int32_t boostAmount,int32_t maxCd, CItemType* amoCostType, uint32_t amoRechargeRate, uint32_t maxAmo, uint32_t amoCost, uint32_t enegyCost){
	this->_boostType = boostType;
	this->_boostAmount = boostAmount;
	this->_maxCd = maxCd;
	this->_enegyCost = enegyCost;
	this->_amoCost = amoCost;
	this->_maxAmo = maxAmo;
	this->_amoCostType = amoCostType;
	this->_amoRechargeRate = amoRechargeRate;
}



CSubTypeBoost::~CSubTypeBoost() {
}

