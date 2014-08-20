/* 
 * File:   CommandMetaHit.cpp
 * Author: karsten
 * 
 * Created on 17. juli 2014, 16:14
 */

#include "CommandMetaHit.h"
#include "Processor.h"
#include "../Sspacebjects/SShot.h"

CommandMetaHit::CommandMetaHit(uint32_t shot, uint32_t target, Shields::Enum shield, int32_t x, int32_t y):
Command(0){
	_shot = shot;
	_target = target;
	_shield = shield;
	_x = x;
	_y = y;
}

uint32_t CommandMetaHit::execute(){
	SShot* shot = NULL;
	//cerr<<"execure metahit"<<endl;
	if(_processor->getLocalProcssable(_shot) && (shot = _processor->getLocalProcssable(_shot)->isShot())){
		shot->Hit(_target,_shield, _x, _y);
	}
	return COMMAND_FINAL;
}


CommandMetaHit::~CommandMetaHit() {
}

