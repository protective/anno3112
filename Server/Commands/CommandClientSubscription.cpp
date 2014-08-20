/* 
 * File:   CommandClientSubscription.cpp
 * Author: karsten
 * 
 * Created on 17. april 2014, 09:36
 */

#include "CommandClientSubscription.h"
#include "Processable.h"
#include "Processor.h"

CommandClientSubscription::CommandClientSubscription(uint32_t time, uint32_t client, uint32_t target, SubscriptionLevel::Enum level):
Command(time){
	_client = client; 
	_target = target;
	_level = level;
}

uint32_t CommandClientSubscription::execute(){
	cerr<<"execute client subsction id="<<_client<<" objid="<<_target<<endl;
	Processable* temp = networkControl->getProcessable(_target);
	
	if(temp)
		temp->subscribeClient(_client, _level);
	else
		cerr<<"ERROR commandClientSubsribe not found"<<endl;
	return COMMAND_FINAL;
}

CommandClientSubscription::~CommandClientSubscription() {
}

