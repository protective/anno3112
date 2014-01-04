/* 
 * File:   SAstoroidType.cpp
 * Author: karsten
 * 
 * Created on 21. oktober 2011, 19:26
 */

#include "SAstoroidType.h"

SAstoroidType::SAstoroidType(uint32_t id) {
	this->_id = id;
	this->_itemType = NULL;
	this->_minQuan = 0;
	this->_maxQuan = 0;
	this->_size = 0;
	this->_texture = 0;
	this->_name = "";

}


SAstoroidType::~SAstoroidType() {
}

