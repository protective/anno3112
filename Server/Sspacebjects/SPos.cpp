/* 
 * File:   SPos.cpp
 * Author: karsten
 * 
 * Created on 24. maj 2011, 19:12
 */

#include "SPos.h"
#include "../World/SGrid.h"
SPos::SPos() {
}

SPos::SPos(int32_t x, int32_t y, int32_t d) {
	this->x = x;
	this->y = y;
	this->d = d;
	this->z = 0;
	this->grid = NULL;
}
SPos::SPos(SGrid* grid, int32_t x, int32_t y, int32_t d) {
	this->x = x;
	this->y = y;
	this->d = d;
	this->z = 0;
	this->grid = grid;
}

void SPos::turn(int32_t deg){
	this->d += deg;
	if (this->d >= 36000){
		this->d -= 36000;
	}
	if (this->d < 0){
		this->d += 36000;
	}
}

SPos::SPos(SPos& pos) {
	this->x = pos.x;
	this->y = pos.y;
	this->d = pos.d;
	this->z = pos.z;
	this->grid = pos.grid;
}

SPos::~SPos() {
}

