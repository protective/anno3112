
#include "SOrdersSystemCalls.h"
#include "../../Commands/Processor.h"
#include "../../Commands/Query/CommandQuery.h"
#include "../../Commands/CargoCommands/CommandCargoTransfere.h"
#include "CommandOrderThread.h"
#include "../SUnit.h"
#include "../SProgrammable.h"
#include "../../World/SWorld.h"


void systemSetSubsystemFlags(Processor* processor, Command* thread,  SProgrammable* obj, void* arg){

	cerr<<"arg"<<endl;
	for(int i = 0; i< 5; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	cerr<<"systemSetSubsystemFlags :D"<<endl;
	uint32_t _subId = ((uint32_t*)arg)[1];
	uint32_t _statusField = ((uint32_t*)arg)[2];
	cerr<<"execute CommandISubStatusField"<<endl;

	SUnit* unit = obj->isUnit();

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


void systemSleep(Processor* processor, Command* thread,  SProgrammable* obj, void* arg){

	
	cerr<<"systemSleep arg"<<endl;
	for(int i = 0; i< 2; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	cerr<<"systemSleep t="<<((uint32_t*)arg)[1]<<endl;
	
	thread->setTime(world->getTime() + ((uint32_t*)arg)[1]);
	obj->yeld();
}


void qureyItems(Processor* processor, Command* thread,  SProgrammable* obj, void* arg){

	
	cerr<<"qureyItems arg"<<endl;
	for(int i = 0; i< 5; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	uint32_t attri = (((uint32_t*)arg)[1]) | (1<<31);
	uint32_t conditionattri = ((uint32_t*)arg)[2] ;
	uint32_t op = ((uint32_t*)arg)[3];
	uint32_t value = ((uint32_t*)arg)[4];
	qureyOrderBy order(1, attri);
	list<qureyCondition> conditions;
	
	qureyCondition q((qureyOperator::Enum)op, conditionattri, value);
	conditions.push_back(q);
	
	CommandQuery* cmd = new CommandQuery(obj->getId(),order,conditions,1);
	processor->addCommand(cmd);
}


void transfereItems(Processor* processor, Command* thread,  SProgrammable* obj, void* arg){

	
	cerr<<"transfereItems arg"<<endl;
	for(int i = 0; i< 4; i++){
		cerr<<((uint32_t*)arg)[i]<<" ";
	}
	cerr<<endl;
	uint32_t from = ((uint32_t*)arg)[1];
	uint32_t itemid = ((uint32_t*)arg)[2];
	uint32_t quan = ((uint32_t*)arg)[3];

	CommandCargoTransfere* cmd = new CommandCargoTransfere(from,obj->getId(),itemid,quan);
	if(networkControl->addCommandToProcesable(cmd,from))
		delete cmd;
}
