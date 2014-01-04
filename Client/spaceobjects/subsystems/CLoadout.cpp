/* 
 * File:   CLoadout.cpp
 * Author: karsten
 * 
 * Created on 1. marts 2012, 20:04
 */

#include "CLoadout.h"

CLoadout::CLoadout(uint32_t id, string name, CShipType& shipType) {
	_id = id;
	_shipType = &shipType;
	_name = name;
}

CLoadout::~CLoadout() {
}

