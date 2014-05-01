/* 
 * File:   CommandIUnfit.cpp
 * Author: karsten
 * 
 * Created on 26. april 2014, 17:01
 */

#include "CommandIUnfit.h"

CommandIUnfit::CommandIUnfit(uint32_t fromId, uint32_t toId, uint32_t subid, uint32_t itemid, uint32_t quantity, uint32_t clientId):
Command(0){
	_fromId = fromId;
	_toId = toId;
	_subid = subid;
	_itemid = itemid;
	_quantity = quantity;
	_clientId = clientId;
}
uint32_t CommandIUnfit::execute(){

}


CommandIUnfit::~CommandIUnfit() {
}

