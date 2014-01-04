/* 
 * File:   CPos.cpp
 * Author: karsten
 * 
 * Created on 23. maj 2011, 10:46
 */

#include "CPos.h"
#include "../world/CGrid.h"
CPos::CPos() {
	this->grid = NULL;
}


CPos::CPos(int32_t x, int32_t y, int32_t d) {
	this->x = x;
	this->y = y;
	this->d = d;
	this->grid = NULL;
}

void CPos::turn(int32_t deg){
	this->d += deg;
	if (this->d >= 36000){
		this->d -= 36000;
	}
	if (this->d < 0){
		this->d += 36000;
	}
}

CPos::CPos(CPos& pos) {
	this->x = pos.x;
	this->y = pos.y;
	this->d = pos.d;
	this->grid = pos.grid;
}

CPos::~CPos() {
}

