/* 
 * File:   CommandIFit.cpp
 * Author: karsten
 * 
 * Created on 26. april 2014, 17:02
 */

#include "CommandIFit.h"

CommandIFit::CommandIFit(uint32_t fromId, uint32_t subid, uint32_t toId, uint32_t quantity, uint32_t clientId):
Command(0){
	_fromId = fromId;
	_subid = subid;
	_toId = toId;
	_quantity = quantity;
	_clientId = clientId;
}
uint32_t CommandIFit::execute(){

}

CommandIFit::~CommandIFit() {
}

