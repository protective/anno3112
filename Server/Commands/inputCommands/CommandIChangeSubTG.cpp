/* 
 * File:   CommandIChangeSubTG.cpp
 * Author: karsten
 * 
 * Created on 15. august 2014, 23:55
 */

#include "CommandIChangeSubTG.h"
#include "../../Sspacebjects/SUnit.h"

CommandIChangeSubTG::CommandIChangeSubTG(uint32_t shipId, uint32_t subId, TargetGroup::Enum targetGroup, uint32_t clientId) :
Command(0){
	_shipId = shipId;
	_subId  = subId;
	_targetGroup = targetGroup;
	_clientId = clientId;
}

uint32_t CommandIChangeSubTG::execute(){
	
	cerr<<"execute CommandIChangeSubTG"<<endl;

	Processable *tproc = _processor->getLocalProcssable(_shipId);
	if (!tproc)
		return COMMAND_FINAL;
	SUnit* unit = tproc->isUnit();
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

	slotnode->second->getSS()->setTargetGroup(_targetGroup);
	slotnode->second->getSS()->reportCharge(SubscriptionLevel::details);
	return COMMAND_FINAL;
}

CommandIChangeSubTG::~CommandIChangeSubTG() {
}

