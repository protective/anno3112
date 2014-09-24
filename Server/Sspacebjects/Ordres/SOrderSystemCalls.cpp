
#include "SOrdersSystemCalls.h"
#include "../../Commands/Processor.h"
#include "CommandOrderThread.h"
#include "../SUnit.h"
#include "../../World/SWorld.h"


void systemSetSubsystemFlags(Processor* processor, Command* thread,  OBJID obj, void* arg){

	cerr<<"arg"<<endl;
	for(int i = 0; i< 5; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	cerr<<"systemSetSubsystemFlags :D"<<endl;
	uint32_t _subId = ((uint32_t*)arg)[1];
	uint32_t _statusField = ((uint32_t*)arg)[2];
	cerr<<"execute CommandISubStatusField"<<endl;
	if(processor->getLocalProcssables().find(obj) == processor->getLocalProcssables().end()){
		cerr<<"CommandTargetPosUpdate target unit not on processor"<<endl;
		return;
	}
	SUnit* unit = processor->getLocalProcssables()[obj]->isUnit();

	if (!unit)
		return ;
	
	//TODO CHECK TEAM
	//if(unit->getTeam() != _client->getTeamId())
	//	break;
	map<uint32_t, SSlotNode*>::iterator slotnode;
	slotnode = unit->getsubable()->getSlots().find(_subId);
	if (slotnode == unit->getsubable()->getSlots().end())
		return;

	if (!slotnode->second->getSS())
		return;

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


void systemSleep(Processor* processor, Command* thread,  OBJID obj, void* arg){

	cerr<<"arg"<<endl;
	for(int i = 0; i< 5; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	cerr<<"systemSleep t="<<((uint32_t*)arg)[1]<<endl;
	thread->setTime(world->getTime() + ((uint32_t*)arg)[1]);
}
