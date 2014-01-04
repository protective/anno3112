/* 
 * File:   CShipType.cpp
 * Author: karsten
 * 
 * Created on 21. august 2011, 11:19
 */

#include "CShipType.h"

CShipType::CShipType(uint32_t id) {
	_texture = 1;
	_id = id;
	_cargo = 0;
	_size = 1;
	_mass = 1;
}

CShipType::~CShipType() {
}

