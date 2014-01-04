/* 
 * File:   SItemType.cpp
 * Author: karsten
 * 
 * Created on 30. juni 2011, 17:18
 */

#include "SItemType.h"
#include "../Sspacebjects/subsystems/SSubType.h"
SItemType::SItemType(uint32_t typeID) {
	this->_typeID = typeID;
	this->_buildTime = 0;
	this->_mass = 0;
	this->_batchSize = 1;
	this->_refineBatch = 0;

	_name = "";
	_subtype = NULL;
	_shiptype = NULL;
	_texid = 0;


}

SSubType* SItemType::getSubType(){
	return this->_subtype;
}

void SItemType::setSubType(SSubType* subtype){
	this->_subtype = subtype;
}
SItemType::~SItemType() {
}

