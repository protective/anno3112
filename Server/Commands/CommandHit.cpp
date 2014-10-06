/* 
 * File:   CommandHit.cpp
 * Author: karsten
 * 
 * Created on 1. juni 2014, 22:27
 */

#include "CommandHit.h"
#include "Processor.h"
#include "../Sspacebjects/STargetable.h"
CommandHit::CommandHit(uint32_t target, uint32_t shot, OBJID owner, uint32_t dmg, DmgTypes::Enum dmgType, Shields::Enum impact, int32_t x, int32_t y) :
Command(0){
	_target = target;
	_shot = shot;
	_owner = owner;
	_dmg = dmg;
	_dmgType = dmgType;
	_impact = impact;
	_x = x;
	_y = y;
}

uint32_t CommandHit::execute(){
	Processable* temp = _processor->getLocalProcssable(_target);
	if (!temp || !temp->isTargetable())
		return COMMAND_FINAL;
	temp->isTargetable()->hit(_shot, _owner, _dmg, _dmgType, _impact, _x, _y);
	return COMMAND_FINAL;
}

CommandHit::~CommandHit() {
}

