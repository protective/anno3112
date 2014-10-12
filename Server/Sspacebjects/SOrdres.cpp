/* 
 * File:   SOrdres.cpp
 * Author: karsten
 * 
 * Created on 8. oktober 2011, 21:05
 */

#include "SOrdres.h"

SOrdres::SOrdres(string name, uint32_t id) {
	_automoveRange = 0;
	_name = name;
	_id = id;
	_program = "";
}

SOrdres::~SOrdres() {
}

