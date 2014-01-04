/* 
 * File:   AChoice.cpp
 * Author: karsten
 * 
 * Created on 29. juni 2012, 20:05
 */

#include "AChoice.h"

AChoice::AChoice(int32_t power, int32_t tactical, int32_t economic, AOrdre* ordre, ABeacon* affectedBeacon) {
	_power = power;
	_tactical = tactical;
	_economic = economic;
	_ordre = ordre;
	_affectedBeacon = affectedBeacon;
}

AChoice::~AChoice() {
	delete _ordre;
}

