/* 
 * File:   CommandISubStatusField.cpp
 * Author: karsten
 * 
 * Created on 26. april 2014, 16:59
 */

#include "CommandISubStatusField.h"
#include "../Processor.h"
#include "../../Sspacebjects/subsystems/SSlotNode.h"
#include "../../Sspacebjects/SUnit.h"
CommandISubStatusField::CommandISubStatusField(uint32_t shipId, uint32_t subId, uint32_t statusField, uint32_t clientId):
Command(0){
	_shipId = shipId;
	_subId  = subId;
	_statusField = statusField;
	_clientId = clientId;
}

uint32_t CommandISubStatusField::execute(){
	cerr<<"execute status change"<<endl;
	if(_processor->getLocalProcssable().find(_shipId) == _processor->getLocalProcssable().end()){
		cerr<<"CommandTargetPosUpdate target unit not on processor"<<endl;
		return COMMAND_FINAL;
	}
	SUnit* unit = _processor->getLocalProcssable()[_shipId]->isUnit();

	if (!unit)
		return COMMAND_FINAL;
	
	//TODO CHECK TEAM
	//if(unit->getTeam() != _client->getTeamId())
	//	break;
	map<uint32_t, SSlotNode*>::iterator slotnode;
	slotnode = unit->getsubable()->getSlots().find(_subId);
	if (slotnode == unit->getsubable()->getSlots().end())
		return COMMAND_FINAL;

	if (!slotnode->second->getSS())
		return COMMAND_FINAL;

	cerr<<"execute status change set status"<<endl;
	slotnode->second->getSS()->setOnline(_statusField & BitF_online);
	if(slotnode->second->getSS()->isWeapon()){
		if(slotnode->second->getSS()->isWeapon()->getTypeWep()->getAmoCostType() == NULL)
			slotnode->second->getSS()->setRecharge(_statusField & BitF_rechargin);
		else if(_statusField & BitF_rechargin)
			slotnode->second->getSS()->setRecharge(true);
	}else if(slotnode->second->getSS()->isBoost()){
		slotnode->second->getSS()->setRecharge(_statusField & BitF_rechargin);
	}
	slotnode->second->getSS()->reportCharge(SubscriptionLevel::details);
}
CommandISubStatusField::~CommandISubStatusField() {
}

