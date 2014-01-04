/* 
 * File:   CSubAble.cpp
 * Author: karsten
 * 
 * Created on 1. august 2011, 00:00
 */

#include "CSubAble.h"

CSubAble::CSubAble(CObj* obj,uint32_t energy,  uint32_t scanRange, uint32_t scanPRange, uint32_t cargo) {
	this->_obj = obj;
	this->_cargoBay = new CCargoBay(this,cargo);
	this->slots.clear();
	this->_scanRange = scanRange * 100;
	this->_scanPRange = scanPRange * 100;
	this->_energy = energy * 1000;
}



CSubAble::~CSubAble() {
}

